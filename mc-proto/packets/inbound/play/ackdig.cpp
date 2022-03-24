#include "ackdig.h"

namespace minecraft
{
    InboundAckDigPacket::InboundAckDigPacket(mcstream& stream)
    {
        stream >> *this;
    }

    position InboundAckDigPacket::pos() const
    {
        return m_blockLocation;
    }

    int InboundAckDigPacket::block() const
    {
        return m_block.val();
    }

    BlockDigStatus InboundAckDigPacket::status() const
    {
        return (BlockDigStatus)m_status.val();
    }

    bool InboundAckDigPacket::success() const
    {
        return m_success;
    }

    string InboundAckDigPacket::to_string() const
    {
        stringstream s;
        s << endl
            << "\tposition: " << m_blockLocation << endl
            << "\tblock: " << m_block.val() << endl
            << "\tstatus: " << m_status.val() << endl
            << "\tsuccess: " << m_success;

        return s.str();
    }

    mcstream& operator>>(mcstream& stream, InboundAckDigPacket& p)
    {
        return stream
            >> p.m_blockLocation
            >> p.m_block
            >> p.m_status
            >> p.m_success;
    }
}