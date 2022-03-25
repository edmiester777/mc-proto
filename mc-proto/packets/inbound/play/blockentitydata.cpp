#include "blockentitydata.h"

namespace minecraft
{
    InboundBlockEntityDataPacket::InboundBlockEntityDataPacket(mcstream& stream)
    {
        stream >> *this;
    }

    position InboundBlockEntityDataPacket::pos() const
    {
        return m_pos;
    }

    int InboundBlockEntityDataPacket::blockType() const
    {
        return m_type.val();
    }

    NBTTagPtr InboundBlockEntityDataPacket::data() const
    {
        return m_data;
    }

    string InboundBlockEntityDataPacket::to_string() const
    {
        stringstream s;
        s << endl
            << "\tpos: " << m_pos << endl
            << "\tblock type: " << m_type.val() << endl
            << "\tdata tag name: " << ((NBTCompoundTag*)m_data.get())->name();
        return s.str();
    }

    mcstream& operator>>(mcstream& stream, InboundBlockEntityDataPacket& p)
    {
        stream
            >> p.m_pos
            >> p.m_type;

        p.m_data = read_nbt_from_stream_with_type(NBTTagTypes::TAG_COMPOUND, stream);

        return stream;
    }
}