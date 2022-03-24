#pragma once

#include "../../packet.h"
#include "../../states.h"
#include "../../../minecraft/types.h"

namespace minecraft
{
    class InboundSpawnPlayerPacket : public Packet
    {
        PACKET_IMPL(InboundSpawnPlayerPacket, States::PLAY, PlayPacketIds::I_SPAWN_PLAYER)
    public:
        InboundSpawnPlayerPacket(mcstream& stream);

        int entityId() const;
        uuid uid() const;
        double x() const;
        double y() const;
        double z() const;
        angle pitch() const;
        angle yaw() const;

        string to_string() const override;

        friend mcstream& operator>>(mcstream& stream, InboundSpawnPlayerPacket& p);

    private:
        int m_entityId;
        uuid m_uuid;
        double m_x;
        double m_y;
        double m_z;
        angle m_pitch;
        angle m_yaw;
    };
}