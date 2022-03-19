#include "client.h"
#include <glog/logging.h>
#include "packets/outbound/handshake.h"
#include "packets/outbound/status.h"

minecraft::Client::Client(string host, int16_t port)
{
    m_host = host;
    m_port = port;
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
            << sockpp::inet_address(m_host, m_port)
            << " with error: " << m_connector.last_error_str();

        return false;
    }

    LOG(INFO) << "Sending handshake packet...";
    OutboundHandshakePacket handshake(m_host, m_port, States::STATUS);
    VLOG(VLOG_DEBUG) << handshake;
    write_packet(handshake);
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
        //LOG(INFO) << "Attempting to read packet...";
        m_mainMutex.lock();
        bool err;

        bool connected = m_connector.is_open();
        m_mainMutex.unlock();

        if (!connected)
            break;
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
    int written = m_connector.write_n(buffer.data(), buffer.size());
    if (written != buffer.size())
    {
        LOG(ERROR)
            << "Did not send full buffer for packet ." << endl
            << "\tbuffer size: " << buffer.size() << endl
            << "\tsent size  : " << written << endl
            << "\tpacket     :" << packet;
    }
}
