#pragma once

#include "../../packet.h"
#include "../../states.h"

namespace minecraft
{
    class InboundSpawnLivingEntityPacket : public Packet
    {
        PACKET_IMPL(InboundSpawnLivingEntityPacket, States::PLAY, PlayPacketIds::I_SPAWN_ENTITY)
    public:
        InboundSpawnLivingEntityPacket(mcstream& stream);

        int entityId() const;
        uuid entityUniqueId() const;
        EntityMetadataType entityType() const;
        double x() const;
        double y() const;
        double z() const;
        int16_t velocityX() const;
        int16_t velocityY() const;
        int16_t velocityZ() const;
        uint8_t yaw() const;
        uint8_t pitch() const;
        uint8_t headYaw() const;

        string to_string() const override;


        friend mcstream& operator>>(mcstream& stream, InboundSpawnLivingEntityPacket& p);

    private:
        int m_entityId;
        uuid m_entityUUID;
        EntityMetadataType m_entityType;
        double m_x;
        double m_y;
        double m_z;
        i16 m_velX;
        i16 m_velY;
        i16 m_velZ;
        u8 m_yaw;
        u8 m_pitch;
        u8 m_headYaw;
    };
}