#pragma once

#include "../../packet.h"
#include "../../states.h"

namespace minecraft
{
    /**
     * Keep alive packet: https://wiki.vg/Protocol#Keep_Alive
     *
     * Also used as pong packet: https://wiki.vg/Protocol#Keep_Alive_.28serverbound.29
     */
    class InboundKeepalivePacket : public Packet
    {
        PACKET_IMPL(InboundKeepalivePacket, States::PLAY, PlayPacketIds::I_KEEPALIVE)
    public:
        InboundKeepalivePacket(int64_t id);
        InboundKeepalivePacket(mcstream& stream);

        int64_t pingId() const;
        string to_string() const override;

        virtual void serialize_data(safebytebuffer& buf) const override;

        friend mcstream& operator>>(mcstream& stream, InboundKeepalivePacket& packet);

    private:
        int64_t m_id;
    };
}