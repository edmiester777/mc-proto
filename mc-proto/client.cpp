#include "client.h"
#include <glog/logging.h>

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
    m_mutex.lock();
    uint64_t packets = m_numPacketsSent;
    m_mutex.unlock();
    return packets;
}

uint64_t minecraft::Client::getNumPacketsReceived()
{
    m_mutex.lock();
    uint64_t packets = m_numPacketsReceived;
    m_mutex.unlock();
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
        m_mutex.lock();
        bool err;
        m_uncompressedPacketReader.readPacket((sockpp::stream_socket&)m_connector, err);

        bool connected = m_connector.is_open();
        m_mutex.unlock();

        if (!connected)
            break;
    }

    LOG(INFO)
        << "Connection to " << m_connector.address() << " has been broken.";
}
