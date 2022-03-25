#include "blockaction.h"

namespace minecraft
{
    InboundBlockActionPacket::InboundBlockActionPacket(mcstream& stream)
    {
        stream >> *this;
    }

    position InboundBlockActionPacket::pos() const
    {
        return m_pos;
    }

    u8 InboundBlockActionPacket::actionId() const
    {
        return m_actionId;
    }

    u8 InboundBlockActionPacket::actionParam() const
    {
        return m_actionParam;
    }

    int InboundBlockActionPacket::blockType() const
    {
        return m_blockType.val();
    }

    string InboundBlockActionPacket::to_string() const
    {
        stringstream s;
        s << endl
            << "\tblock type: " << blockType() << endl
            << "\tposition: " << m_pos << endl
            << "\taction id: " << (int)m_actionId << " param: " << (int)m_actionParam;
        return s.str();
    }

    mcstream& operator>>(mcstream& stream, InboundBlockActionPacket& p)
    {
        return stream
            >> p.m_pos
            >> p.m_actionId >> p.m_actionParam
            >> p.m_blockType;
    }
}