#include "spawnentity.h"
#include <iomanip>

namespace minecraft
{
    InboundSpawnEntityPacket::InboundSpawnEntityPacket(mcstream& stream)
    {
        stream >> *this;
    }

    int InboundSpawnEntityPacket::entityId() const
    {
        return m_entityId;
    }

    uuid InboundSpawnEntityPacket::entityUniqueId() const
    {
        return m_entityUUID;
    }

    EntityMetadataType InboundSpawnEntityPacket::entityType() const
    {
        return m_entityType;
    }

    double InboundSpawnEntityPacket::x() const
    {
        return m_x;
    }

    double InboundSpawnEntityPacket::y() const
    {
        return m_y;
    }

    double InboundSpawnEntityPacket::z() const
    {
        return m_z;
    }

    i16 InboundSpawnEntityPacket::velocityX() const
    {
        return m_velX;
    }

    i16 InboundSpawnEntityPacket::velocityY() const
    {
        return m_velY;
    }

    i16 InboundSpawnEntityPacket::velocityZ() const
    {
        return m_velZ;
    }

    angle InboundSpawnEntityPacket::yaw() const
    {
        return m_yaw;
    }

    angle InboundSpawnEntityPacket::pitch() const
    {
        return m_pitch;
    }

    int InboundSpawnEntityPacket::data() const
    {
        return m_data;
    }

    string InboundSpawnEntityPacket::to_string() const
    {
        stringstream stream;
        stream
            << endl
            << "\tid: " << m_entityId << endl
            << "\tuuid: " << m_entityUUID << endl
            << "\ttype: " << setw(4) << setfill(' ') << (int)m_entityType << " " << ENTITY_TYPE_TO_STRING[m_entityType] << endl
            << "\tposition (" << m_x << ", " << m_y << ", " << m_z << ")" << endl
            << "\tvelocity (" << m_velX << ", " << m_velY << ", " << m_velZ << ")" << endl
            << "\tpitch: " << (short)m_pitch << " yaw: " << (short)m_yaw << endl
            << "\tdata: " << m_data;

        return stream.str();
    }

    mcstream& operator>>(mcstream& stream, InboundSpawnEntityPacket& p)
    {
        varint entityId;
        varint entityType;
        stream
            >> entityId
            >> p.m_entityUUID
            >> entityType
            >> p.m_x >> p.m_y >> p.m_z
            >> p.m_yaw >> p.m_pitch
            >> p.m_data
            >> p.m_velX >> p.m_velY >> p.m_velZ;

        p.m_entityId = entityId.val();
        p.m_entityType = (EntityMetadataType)entityType.val();

        return stream;
    }

}