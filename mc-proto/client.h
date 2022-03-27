#pragma once

#include <string>
#include <mutex>
#include <memory>
#include <sockpp/tcp_connector.h>
#include "clientlistener.h"

namespace minecraft
{
    using namespace std;
    class Packet;
    enum class States;

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
        Client(string host, i16 port, sp<ClientEventListener> listener);
        virtual ~Client();

        u64 getNumPacketsSent();
        u64 getNumPacketsReceived();

        bool overworld() const;

        bool connect();
        void login(string username);

        /**
         * Main connection loop. This will block until connection is
         * broken.
         */
        void run();

        void write_packet(const Packet& packet);

    protected:
        void read_packet();
    private:
        bool m_overworld;
        States m_state;
        string m_host;
        in_port_t m_port;
        sockpp::socket_initializer m_sockInitializer;
        sockpp::tcp_connector m_connector;
        mutex m_mainMutex;
        mutex m_writeMutex;
        uint64_t m_numPacketsSent;
        uint64_t m_numPacketsReceived;
        sp<ClientEventListener> m_listener;
    };
}