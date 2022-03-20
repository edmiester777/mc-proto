#pragma once

#include "../packet.h"
#include "../states.h"

namespace minecraft
{
    class InboundStatusPacket : public Packet
    {
        PACKET_IMPL(InboundStatusPacket, States::STATUS, StatusPacketIds::I_STATUS)
    public:
        InboundStatusPacket(mcstream& input);

        string to_string() const override;

    private:
        string m_responseStr;
    };
}