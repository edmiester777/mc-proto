#pragma once

#include "../packet.h"
#include "../states.h"

namespace minecraft
{
    class OutboundStatusPacket : public Packet
    {
        PACKET_IMPL(OutboundStatusPacket, States::STATUS, StatusPacketIds::O_STATUS)
    public:
        OutboundStatusPacket();
        OutboundStatusPacket(safebytebuffer& buffer);

        virtual void serialize_data(safebytebuffer& buffer) const override;
        virtual string to_string() const override;
    };
}