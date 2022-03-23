#pragma once

#include "../../inbound/play/ping.h"

namespace minecraft
{
    class OutboundPingPacket : public InboundPingPacket
    {
        PACKET_IMPL(OutboundPingPacket, States::PLAY, PlayPacketIds::O_PING)
    public:
        OutboundPingPacket(int id) : InboundPingPacket(id) { }
    };
}