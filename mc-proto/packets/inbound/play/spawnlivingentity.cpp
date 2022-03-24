#include "spawnlivingentity.h"
#include <iomanip>

namespace minecraft
{
    InboundSpawnLivingEntityPacket::InboundSpawnLivingEntityPacket(mcstream& stream)
    {
        stream >> *this;
    }

    int InboundSpawnLivingEntityPacket::entityId() const
    {
        return m_entityId;
    }

    uuid InboundSpawnLivingEntityPacket::entityUniqueId() const
    {
        return m_entityUUID;
    }

    EntityMetadataType InboundSpawnLivingEntityPacket::entityType() const
    {
        return m_entityType;
    }

    double InboundSpawnLivingEntityPacket::x() const
    {
        return m_x;
    }

    double InboundSpawnLivingEntityPacket::y() const
    {
        return m_y;
    }

    double InboundSpawnLivingEntityPacket::z() const
    {
        return m_z;
    }

    i16 InboundSpawnLivingEntityPacket::velocityX() const
    {
        return m_velX;
    }

    i16 InboundSpawnLivingEntityPacket::velocityY() const
    {
        return m_velY;
    }

    i16 InboundSpawnLivingEntityPacket::velocityZ() const
    {
        return m_velZ;
    }

    angle InboundSpawnLivingEntityPacket::yaw() const
    {
        return m_yaw;
    }

    angle InboundSpawnLivingEntityPacket::pitch() const
    {
        return m_pitch;
    }

    angle InboundSpawnLivingEntityPacket::headYaw() const
    {
        return m_headYaw;
    }

    string InboundSpawnLivingEntityPacket::to_string() const
    {
        stringstream stream;
        stream
            << endl
            << "\tid: " << m_entityId << endl
            << "\tuuid: " << m_entityUUID << endl
            << "\ttype: " << setw(4) << setfill(' ') << (int)m_entityType << " " << ENTITY_TYPE_TO_STRING[m_entityType] << endl
            << "\tposition (" << m_x << ", " << m_y << ", " << m_z << ")" << endl
            << "\tvelocity (" << m_velX << ", " << m_velY << ", " << m_velZ << ")" << endl
            << "\tpitch: " << (short)m_pitch << " yaw: " << (short)m_yaw << " headYaw: " << (short)m_headYaw;

        return stream.str();
    }

    mcstream& operator>>(mcstream& stream, InboundSpawnLivingEntityPacket& p)
    {
        varint entityId;
        varint entityType;
        stream
            >> entityId
            >> p.m_entityUUID
            >> entityType
            >> p.m_x >> p.m_y >> p.m_z
            >> p.m_yaw >> p.m_pitch >> p.m_headYaw
            >> p.m_velX >> p.m_velY >> p.m_velZ;

        p.m_entityId = entityId.val();
        p.m_entityType = (EntityMetadataType)entityType.val();

        return stream;
    }

}