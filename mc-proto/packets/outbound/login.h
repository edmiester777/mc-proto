#pragma once

#include "../packet.h"
#include "../states.h"

namespace minecraft
{
    using namespace std;

    class OutboundLoginPacket : public Packet
    {
        PACKET_IMPL(OutboundLoginPacket, States::LOGIN, LoginPacketIds::O_LOGIN_START)
    public:
        OutboundLoginPacket(string username);

        virtual void serialize_data(safebytebuffer& s) const override;
        
        string username() const;

    private:
        string m_username;
    };
}