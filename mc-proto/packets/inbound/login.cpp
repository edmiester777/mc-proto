#include "login.h"

namespace minecraft
{
    InboundLoginPacket::InboundLoginPacket(mcstream& stream)
    {
        stream >> *this;
    }

    uuid InboundLoginPacket::userId() const
    {
        return m_userId;
    }

    string InboundLoginPacket::username() const
    {
        return m_username;
    }

    string InboundLoginPacket::to_string() const
    {
        stringstream s;
        s << "USERID(" << m_userId.to_string() << ") "
          << "USERNAME(" << m_username << ")";
        return s.str();
    }

    mcstream& operator>>(mcstream& stream, InboundLoginPacket& packet)
    {
        stream >> packet.m_userId >> packet.m_username;
        return stream;
    }
}