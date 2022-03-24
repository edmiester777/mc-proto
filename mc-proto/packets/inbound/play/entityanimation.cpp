#include "entityanimation.h"

namespace minecraft
{
    InboundEntityAnimationPacket::InboundEntityAnimationPacket(mcstream& stream)
    {
        stream >> *this;
    }

    int InboundEntityAnimationPacket::playerEntityId() const
    {
        return m_entityId.val();
    }

    u8 InboundEntityAnimationPacket::animationId() const
    {
        return m_animationId;
    }

    string InboundEntityAnimationPacket::to_string() const
    {
        stringstream s;
        s << "playerId: " << m_entityId.val() << " animationId: " << (int)m_animationId;
        return s.str();
    }

    mcstream& operator>>(mcstream& stream, InboundEntityAnimationPacket& p)
    {
        return stream >> p.m_entityId >> p.m_animationId;
    }
}