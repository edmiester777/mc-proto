#pragma once

#include "../../inbound/play/keepalive.h"

namespace minecraft
{
    class OutboundKeepalivePacket : public InboundKeepalivePacket
    {
        PACKET_IMPL(OutboundKeepalivePacket, States::PLAY, PlayPacketIds::O_KEEPALIVE)
    public:
        OutboundKeepalivePacket(uint64_t id) : InboundKeepalivePacket(id) { }
    };
}