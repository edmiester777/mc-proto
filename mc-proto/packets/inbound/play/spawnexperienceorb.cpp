#include "spawnexperienceorb.h"
#include <iomanip>

namespace minecraft
{
    InboundSpawnExperienceOrbPacket::InboundSpawnExperienceOrbPacket(mcstream& stream)
    {
        stream >> *this;
    }

    EntityMetadataType InboundSpawnExperienceOrbPacket::entityType() const
    {
        return m_entityType;
    }
    double InboundSpawnExperienceOrbPacket::x() const
    {
        return m_x;
    }
    double InboundSpawnExperienceOrbPacket::y() const
    {
        return m_y;
    }
    double InboundSpawnExperienceOrbPacket::z() const
    {
        return m_z;
    }
    int16_t InboundSpawnExperienceOrbPacket::count() const
    {
        return m_count;
    }
    string InboundSpawnExperienceOrbPacket::to_string() const
    {
        stringstream s;
        s << endl
            << "\ttype: " << (int)m_entityType << endl
            << "\tposition: (" << m_x << ", " << m_y << ", " << m_z << ")" << endl
            << "\tcount: " << m_count;

        return s.str();
    }

    mcstream& operator>>(mcstream& stream, InboundSpawnExperienceOrbPacket& p)
    {
        varint type;
        stream >> type
            >> p.m_x >> p.m_y >> p.m_z
            >> p.m_count;

        p.m_entityType = (EntityMetadataType)type.val();
        
        return stream;
    }
}