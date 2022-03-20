#include "client.h"
#include <glog/logging.h>
#include "packets/inbound/status.h"
#include "packets/outbound/handshake.h"
#include "packets/outbound/status.h"
#include "packets/states.h"

using namespace minecraft;

minecraft::Client::Client(string host, int16_t port)
    : m_host(host)
    , m_port(port)
    , m_state(States::HANDSHAKING)
{
}

minecraft::Client::~Client()
{

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

bool minecraft::Client::connect()
{
    m_connector = sockpp::tcp_connector({m_host, m_port});

    if (!m_connector.is_connected())
    {
        LOG(WARNING)
            << "Failed to connect to TCP "
            << m_host << ":" << m_port
            << " with error: " << m_connector.last_error_str();

        return false;
    }

    LOG(INFO) << "Sending handshake packet...";
    OutboundHandshakePacket handshake(m_host, m_port, States::STATUS);
    VLOG(VLOG_DEBUG) << handshake;
    write_packet(handshake);
    m_state = States::STATUS;
    LOG(INFO) << "Sending status packet...";
    OutboundStatusPacket status;
    VLOG(VLOG_DEBUG) << status;

    LOG(INFO)
        << "Created connection to "
        << m_connector.address();

    return true;
}

void minecraft::Client::run()
{
    while (true)
    {
        LOG(INFO) << "Attempting to read packet...";
        m_mainMutex.lock();
        bool connected = m_connector.is_connected();
        m_mainMutex.unlock();

        if (!connected)
            break;

        read_packet();
    }

    LOG(INFO)
        << "Connection to " << m_connector.address() << " has been broken.";
}

void minecraft::Client::write_packet(const Packet& packet)
{
    m_mainMutex.lock();
    bool connected = m_connector.is_open();
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
    lengthbuffer.push(varint(buffer.size()));
    VLOG(VLOG_DEBUG) << "Outgoing packet length: " << buffer.size();
    int written = m_connector.write_n(lengthbuffer.data(), lengthbuffer.size());

    if (written != lengthbuffer.size())
    {
        LOG(ERROR)
            << "Not able to send packet length for packet"
            << packet;
    }

    // writing packet data
    written = m_connector.write_n(buffer.data(), buffer.size());
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
        int read = m_connector.read_n(&b, 1);
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
    int recvd = m_connector.read_n(buf.data(), incoming_packet_len.val());
    buf.push_buffer(buf.data(), incoming_packet_len.val());

    if (recvd != incoming_packet_len.val())
    {
        LOG(WARNING)
            << "Could not receive full packet data." << endl
            << "\tExpected size: " << incoming_packet_len.val() << endl
            << "\tReceived size: " << recvd;
        return;
    }

    // converting to a stream
    mcstream stream;
    stream << buf;

    // getting packet ID
    varint packetId;
    stream >> packetId;
    InboundStatusPacket packet(stream);

    VLOG(VLOG_INFO)
        << "Received packet:" << packet;
}
