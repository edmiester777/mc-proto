#pragma once

#include "../../packet.h"
#include "../../states.h"
#include "../../../nbt/nbt.h"

namespace minecraft
{
    class InboundBlockEntityDataPacket : public Packet
    {
        PACKET_IMPL(InboundBlockEntityDataPacket, States::PLAY, PlayPacketIds::I_BLOCK_ENTITY_DATA)
    public:
        InboundBlockEntityDataPacket(mcstream& stream);

        position pos() const;
        int blockType() const;
        NBTTagPtr data() const;
        string to_string() const override;

        friend mcstream& operator>>(mcstream& stream, InboundBlockEntityDataPacket& p);

    private:
        position m_pos;
        varint m_type;
        NBTTagPtr m_data;
    };
}