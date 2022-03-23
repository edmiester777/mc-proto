#pragma once

#include "../../packet.h"
#include "../../states.h"

namespace minecraft
{
    /**
     * Ping packet: https://wiki.vg/Protocol#Ping_2
     * 
     * Also used as pong packet: https://wiki.vg/Protocol#Pong_2
     */
    class InboundPingPacket : public Packet
    {
        PACKET_IMPL(InboundPingPacket, States::PLAY, PlayPacketIds::I_PING)
    public:
        InboundPingPacket(int id);
        InboundPingPacket(mcstream& stream);

        int32_t pingId() const;
        string to_string() const override;

        virtual void serialize_data(safebytebuffer& buf) const override;

        friend mcstream& operator>>(mcstream& stream, InboundPingPacket& packet);

    private:
        int32_t m_id;
    };
}