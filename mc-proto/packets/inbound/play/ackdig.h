#pragma once

#include "../../packet.h"
#include "../../states.h"
#include "../../../minecraft/types.h"

namespace minecraft
{
    class InboundAckDigPacket : public Packet
    {
        PACKET_IMPL(InboundAckDigPacket, States::PLAY, PlayPacketIds::I_ACKNOWLEGE_DIG)
    public:
        InboundAckDigPacket(mcstream& stream);

        position pos() const;
        int block() const;
        BlockDigStatus status() const;
        bool success() const;

        string to_string() const override;
        friend mcstream& operator>>(mcstream& stream, InboundAckDigPacket& p);

    private:
        position m_blockLocation;
        varint m_block;
        varint m_status;
        bool m_success;
    };
}