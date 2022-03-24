#pragma once

#include "../../packet.h"
#include "../../states.h"

namespace minecraft
{
    class InboundBlockBreakAnimationPacket : public Packet
    {
        PACKET_IMPL(InboundBlockBreakAnimationPacket, States::PLAY, PlayPacketIds::I_BLOCK_BREAK_ANIM)
    public:
        InboundBlockBreakAnimationPacket(mcstream& stream);

        int entityId() const;
        position pos() const;

        /**
         * Stage of animation:
         * 
         * 0-9 sprite index
         * if is other value, remove animation from block
         * 
         * https://wiki.vg/Protocol#Block_Break_Animation
         * 
         * @return stage for block
         */
        u8 stage() const;

        string to_string() const override;
        friend mcstream& operator>>(mcstream& stream, InboundBlockBreakAnimationPacket& p);

    private:
        varint m_entityId;
        position m_pos;
        u8 m_stage;
    };
}