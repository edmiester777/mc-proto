#pragma once

#include <string>
#include <mutex>
#include <sockpp/tcp_connector.h>

namespace minecraft
{
    using namespace std;

    /**
     * Network manager for connecting to a minecraft server. Operations
     * are thread safe.
     * 
     * This object is not copyable. Only a single instance should
     * be created.
     */
    class Client
    {
    public:
        Client(string host, int16_t port);
        virtual ~Client();

        uint64_t getNumPacketsSent();
        uint64_t getNumPacketsReceived();

        bool connect();

        /**
         * Main connection loop. This will block until connection is
         * broken.
         */
        void run();
    private:
        string m_host;
        in_port_t m_port;
        sockpp::socket_initializer m_sockInitializer;
        sockpp::tcp_connector m_connector;
        mutex m_mutex;
        uint64_t m_numPacketsSent;
        uint64_t m_numPacketsReceived;
    };
}