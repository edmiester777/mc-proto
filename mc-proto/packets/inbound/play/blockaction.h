#pragma once

#include "../../packet.h"
#include "../../states.h"

namespace minecraft
{
    class InboundBlockActionPacket : public Packet
    {
        PACKET_IMPL(InboundBlockActionPacket, States::PLAY, PlayPacketIds::I_BLOCK_ACTION)
    public:
        InboundBlockActionPacket(mcstream& stream);

        position pos() const;

        /**
         * ID of action depends on the #blockType().
         * 
         * @see https://wiki.vg/Block_Actions
         */
        u8 actionId() const;

        /**
         * ID of param depends on the #actionId()
         * 
         * @see https://wiki.vg/Block_Actions
         */
        u8 actionParam() const;
        int blockType() const;
        string to_string() const override;
        
        friend mcstream& operator>>(mcstream& stream, InboundBlockActionPacket& p);

    private:
        position m_pos;
        u8 m_actionId;
        u8 m_actionParam;
        varint m_blockType;
    };
}