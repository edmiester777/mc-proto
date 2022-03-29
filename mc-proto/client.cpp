#include "client.h"
#include <sockpp/tcp_connector.h>
#include <glog/logging.h>
#include "packets/inbound/status.h"
#include "packets/inbound/login.h"
#include "packets/inbound/play/spawnentity.h"
#include "packets/outbound/handshake.h"
#include "packets/outbound/status.h"
#include "packets/outbound/login.h"
#include "packets/outbound/play/ping.h"
#include "packets/outbound/play/keepalive.h"

#define SIMPLE_PACKET_READ(id, cls, call) \
    case (id): \
    { \
        sp<cls> tmppacket = sp<cls>(new cls(stream)); \
        m_listener->call(*this, *tmppacket); \
        packet = tmppacket; \
        break; \
    }

#define conn ((sockpp::tcp_connector*)m_connector)

using namespace minecraft;

minecraft::Client::Client(string host, i16 port, sp<ClientEventListener> listener)
    : m_overworld(true)
    , m_host(host)
    , m_port(port)
    , m_listener(listener)
    , m_state(States::HANDSHAKING)
    , m_numPacketsSent(0)
    , m_numPacketsReceived(0)
    , m_connector(nullptr)
    , m_sockInitializer(nullptr)
{
}

minecraft::Client::~Client()
{
    if (m_connector != nullptr)
        delete m_connector;
    if (m_sockInitializer != nullptr)
        delete m_sockInitializer;
}

uint64_t minecraft::Client::getNumPacketsSent()
{
    m_mainMutex.lock();
    uint64_t packets = m_numPacketsSent;
    m_mainMutex.unlock();
    return packets;
}

uint64_t minecraft::Client::getNumPacketsReceived()
{
    m_mainMutex.lock();
    uint64_t packets = m_numPacketsReceived;
    m_mainMutex.unlock();
    return packets;
}

bool minecraft::Client::overworld() const
{
    return m_overworld;
}

bool minecraft::Client::connect()
{
    m_sockInitializer = new sockpp::socket_initializer();
    m_connector = new sockpp::tcp_connector({m_host, m_port});

    if (!conn->is_connected())
    {
        LOG(WARNING)
            << "Failed to connect to TCP "
            << m_host << ":" << m_port
            << " with error: " << conn->last_error_str();

        return false;
    }

    LOG(INFO) << "Sending handshake packet...";
    OutboundHandshakePacket handshake(m_host, m_port, States::LOGIN);
    VLOG(VLOG_DEBUG) << handshake;
    write_packet(handshake);

    LOG(INFO)
        << "Created connection to "
        << conn->address();

    return true;
}

void minecraft::Client::login(string username)
{
    m_mainMutex.lock();
    m_state = States::LOGIN;
    m_mainMutex.unlock();
    write_packet(OutboundLoginPacket(username));
}

void minecraft::Client::run()
{
    while (true)
    {
        VLOG(VLOG_DEBUG) << "Attempting to read packet...";
        m_mainMutex.lock();
        bool connected = conn->is_connected();
        m_mainMutex.unlock();

        if (!connected)
            break;

        read_packet();
    }

    LOG(INFO)
        << "Connection to " << conn->address() << " has been broken.";
}

void minecraft::Client::write_packet(const Packet& packet)
{
    m_mainMutex.lock();
    bool connected = conn->is_open();
    m_mainMutex.unlock();

    if (!connected)
    {
        LOG(ERROR)
            << "Attempted to write packet to a disconnected socket: "
            << packet;
    }

    lock_guard<mutex> writeLock(m_writeMutex);
    safebytebuffer buffer = packet.serialize();

    // writing packet size as var int
    safebytebuffer lengthbuffer;
    lengthbuffer.push(varint((int)buffer.size()));
    VLOG(VLOG_DEBUG) << "Outgoing packet length: " << buffer.size();
    int written = (int)conn->write_n(lengthbuffer.data(), lengthbuffer.size());

    if (written != lengthbuffer.size())
    {
        LOG(ERROR)
            << "Not able to send packet length for packet"
            << packet;
    }

    // writing packet data
    written = (int)conn->write_n(buffer.data(), (int)buffer.size());
    if (written != buffer.size())
    {
        LOG(ERROR)
            << "Did not send full buffer for packet ." << endl
            << "\tbuffer size: " << buffer.size() << endl
            << "\tsent size  : " << written << endl
            << "\tpacket     :" << packet;
    }
}

void minecraft::Client::read_packet()
{
    // reading header for packet length
    varint incoming_packet_len([this] {
        uint8_t b;
        int read = (int)conn->read_n(&b, 1);
        if (read != 1)
        {
            LOG(ERROR) << "Could not read byte from socket for varint.";
            throw exception("Failed to read from socket.");
        }
        return b;
    });

    // reading packet to raw buffer
    safebytebuffer buf;
    buf.reserve(incoming_packet_len.val());
    int recvd = (int)conn->read_n(buf.data(), incoming_packet_len.val());
    buf.push_buffer(buf.data(), incoming_packet_len.val());
    VLOG(VLOG_DEBUG) << "Read packet data in " << incoming_packet_len.val() << " bytes";

    if (recvd != incoming_packet_len.val())
    {
        LOG(WARNING)
            << "Could not receive full packet data." << endl
            << "\tExpected size: " << incoming_packet_len.val() << endl
            << "\tReceived size: " << recvd;
        return;
    }

    // converting to a stream
    shared_ptr<Packet> packet = nullptr;
    mcstream stream;
    stream << buf;

    // getting packet ID
    varint packetId;
    stream >> packetId;

    // logic for packets based on state
    if (m_state == States::LOGIN)
    {
        switch ((LoginPacketIds)packetId.val())
        {
        case LoginPacketIds::I_LOGIN_SUCCESS:
        {
            m_state = States::PLAY;
            shared_ptr<InboundLoginPacket> loginPacket(new InboundLoginPacket(stream));
            m_listener->OnLoginSuccess(*this, *loginPacket);
            packet = loginPacket;
            break;
        }
        case LoginPacketIds::I_DISCONNECT:
            packet = shared_ptr<Packet>(new InboundStatusPacket(stream));
            break;
        }
    }
    else if (m_state == States::PLAY)
    {
        switch ((PlayPacketIds)packetId.val())
        {
            SIMPLE_PACKET_READ(PlayPacketIds::I_SPAWN_ENTITY, InboundSpawnEntityPacket, OnSpawnEntity)
            SIMPLE_PACKET_READ(PlayPacketIds::I_SPAWN_EXPERIENCE_ORB, InboundSpawnExperienceOrbPacket, OnSpawnExperienceOrb)
            SIMPLE_PACKET_READ(PlayPacketIds::I_SPAWN_LIVING_ENTITY, InboundSpawnLivingEntityPacket, OnSpawnLivingEntity)
            SIMPLE_PACKET_READ(PlayPacketIds::I_SPAWN_PAINTING, InboundSpawnPaintingPacket, OnSpawnPainting)
            SIMPLE_PACKET_READ(PlayPacketIds::I_SPAWN_PLAYER, InboundSpawnPlayerPacket, OnSpawnPlayer)
            SIMPLE_PACKET_READ(PlayPacketIds::I_PLAYER_ANIATION, InboundEntityAnimationPacket, OnPlayerAnimation)
            SIMPLE_PACKET_READ(PlayPacketIds::I_ACKNOWLEGE_DIG, InboundAckDigPacket, OnBlockDigAcknowleged)
            SIMPLE_PACKET_READ(PlayPacketIds::I_BLOCK_BREAK_ANIM, InboundBlockBreakAnimationPacket, OnBlockBreakAnimation)
            SIMPLE_PACKET_READ(PlayPacketIds::I_BLOCK_ENTITY_DATA, InboundBlockEntityDataPacket, OnBlockData)
            SIMPLE_PACKET_READ(PlayPacketIds::I_BLOCK_ACTION, InboundBlockActionPacket, OnBlockAction)
        case PlayPacketIds::I_PING:
            {
                // received a ping... we must reply with a pong
                sp<InboundPingPacket> pingpacket(new InboundPingPacket(stream));
                write_packet(OutboundPingPacket(pingpacket->pingId()));
                packet = pingpacket;
                break;
            }
        case PlayPacketIds::I_KEEPALIVE:
            {
                // received keepalive... does same thing as ping
                sp<InboundKeepalivePacket> keepalive(new InboundKeepalivePacket(stream));
                write_packet(OutboundKeepalivePacket(keepalive->pingId()));
                packet = keepalive;
                break;
            }
        case PlayPacketIds::I_CHUNK_DATA:
            {
                sp<InboundChunkDataPacket> chunk(new InboundChunkDataPacket(stream, m_overworld));
                m_listener->OnChunkData(*this, *chunk);
                packet = chunk;
                break;
            }
        }
    }

    if (packet)
    {
        VLOG(VLOG_INFO)
            << "Received packet:" << endl
            << "\tsize: " << incoming_packet_len.val() << endl
            << "\tstate: " << setw(2) << setfill('0') << (int)m_state << endl
            << "\tcontent: { " << *packet << " }";
    }
    else
    {
        // disabling until all packets are implemented
        // 
        //LOG(WARNING)
        //    << "Could not read packet with ID "
        //    << "0x" << setw(2) << setfill('0') << packetId.val()
        //    << "for state 0x" << setw(2) << setfill('0') << (int)m_state;
    }
}
