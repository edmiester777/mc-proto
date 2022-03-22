#pragma once

#include "../packet.h"
#include "../states.h"

namespace minecraft
{
    class InboundLoginPacket : public Packet
    {
        PACKET_IMPL(InboundLoginPacket, States::LOGIN, LoginPacketIds::I_LOGIN_SUCCESS)
    public:
        InboundLoginPacket(mcstream& stream);

        uuid userId() const;
        string username() const;

        virtual string to_string() const override;

        friend mcstream& operator>>(mcstream& stream, InboundLoginPacket& packet);

    private:
        uuid m_userId;
        string m_username;
    };
}