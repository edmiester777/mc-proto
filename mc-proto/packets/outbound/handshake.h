#pragma once

#include "../packet.h"
#include "../states.h"

namespace minecraft
{
    class OutboundHandshakePacket : public Packet
    {
    public:
        OutboundHandshakePacket(safebytebuffer buf);

        /**
         * Construct a client handshake packet with parameters.
         * 
         * @param serverAddr Address used to connect to this server.
         * @param port Port that was connected to.
         * @param nextState Next state (STATUS/LOGIN) to be requested.
         */
        OutboundHandshakePacket(
            string serverAddr,
            uint16_t port,
            States nextState
        );

        virtual int id() const override;
        virtual void serialize_data(safebytebuffer& buf) const override;

    private:
        string m_serverAddr;
        uint16_t m_port;
        States m_nextState;
    };
}