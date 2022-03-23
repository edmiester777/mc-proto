#include "keepalive.h"

namespace minecraft
{
    InboundKeepalivePacket::InboundKeepalivePacket(int64_t id) : m_id(id)
    {
    }

    InboundKeepalivePacket::InboundKeepalivePacket(mcstream& stream)
    {
        stream >> *this;
    }

    int64_t InboundKeepalivePacket::pingId() const
    {
        return m_id;
    }

    string InboundKeepalivePacket::to_string() const
    {
        stringstream s;
        s << "id: " << pingId();
        return s.str();
    }

    void InboundKeepalivePacket::serialize_data(safebytebuffer& buf) const
    {
        buf.push(m_id);
    }

    mcstream& operator>>(mcstream& stream, InboundKeepalivePacket& packet)
    {
        stream >> packet.m_id;
        return stream;
    }
}