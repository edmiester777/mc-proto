#include "spawnplayer.h"

namespace minecraft
{
    InboundSpawnPlayerPacket::InboundSpawnPlayerPacket(mcstream& stream)
    {
        stream >> *this;
    }

    int InboundSpawnPlayerPacket::entityId() const
    {
        return m_entityId;
    }

    uuid InboundSpawnPlayerPacket::uid() const
    {
        return m_uuid;
    }

    double InboundSpawnPlayerPacket::x() const
    {
        return m_x;
    }

    double InboundSpawnPlayerPacket::y() const
    {
        return m_y;
    }

    double InboundSpawnPlayerPacket::z() const
    {
        return m_z;
    }

    angle InboundSpawnPlayerPacket::pitch() const
    {
        return m_pitch;
    }

    angle InboundSpawnPlayerPacket::yaw() const
    {
        return m_yaw;
    }

    string InboundSpawnPlayerPacket::to_string() const
    {
        stringstream s;
        s << endl
            << "\tid: " << m_entityId << endl
            << "\tuuid: " << m_uuid << endl
            << "\tposition: (" << m_x << ", " << m_y << ", " << m_z << ")" << endl
            << "\tpitch: " << (int)m_pitch << " yaw: " << (int)m_yaw;

        return s.str();
    }

    mcstream& operator>>(mcstream& stream, InboundSpawnPlayerPacket& p)
    {
        varint entid;
        stream
            >> entid
            >> p.m_uuid
            >> p.m_x >> p.m_y >> p.m_z
            >> p.m_yaw >> p.m_pitch;

        p.m_entityId = entid.val();

        return stream;
    }
}