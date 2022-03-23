#include "ping.h"

namespace minecraft
{
    InboundPingPacket::InboundPingPacket(int id) : m_id(id)
    {
    }

    InboundPingPacket::InboundPingPacket(mcstream& stream)
    {
        stream >> *this;
    }

    int32_t InboundPingPacket::pingId() const
    {
        return m_id;
    }

    string InboundPingPacket::to_string() const
    {
        stringstream s;
        s << "id: " << pingId();
        return s.str();
    }

    void InboundPingPacket::serialize_data(safebytebuffer& buf) const
    {
        buf.push(m_id);
    }

    mcstream& operator>>(mcstream& stream, InboundPingPacket& packet)
    {
        stream >> packet.m_id;
        return stream;
    }
}