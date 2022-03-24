#include "blockbreakanim.h"

namespace minecraft
{
    InboundBlockBreakAnimationPacket::InboundBlockBreakAnimationPacket(mcstream& stream)
    {
        stream >> *this;
    }

    int InboundBlockBreakAnimationPacket::entityId() const
    {
        return m_entityId.val();
    }

    position InboundBlockBreakAnimationPacket::pos() const
    {
        return m_pos;
    }

    u8 InboundBlockBreakAnimationPacket::stage() const
    {
        return m_stage;
    }

    string InboundBlockBreakAnimationPacket::to_string() const
    {
        stringstream s;
        s << endl
            << "\tentity id: " << entityId() << endl
            << "\tpos: " << pos() << endl
            << "\tstage: " << (int)stage();

        return s.str();
    }

    mcstream& operator>>(mcstream& stream, InboundBlockBreakAnimationPacket& p)
    {
        return stream
            >> p.m_entityId
            >> p.m_pos
            >> p.m_stage;
    }
}