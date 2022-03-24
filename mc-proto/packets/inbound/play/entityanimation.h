#pragma once

#include "../../packet.h"
#include "../../states.h"

namespace minecraft
{
    class InboundEntityAnimationPacket : public Packet
    {
        PACKET_IMPL(InboundEntityAnimationPacket, States::PLAY, PlayPacketIds::I_PLAYER_ANIATION)
    public:
        InboundEntityAnimationPacket(mcstream& stream);

        int playerEntityId() const;
        u8 animationId() const;

        string to_string() const override;
        friend mcstream& operator>>(mcstream& stream, InboundEntityAnimationPacket& p);

    private:
        varint m_entityId;
        u8 m_animationId;
    };
}