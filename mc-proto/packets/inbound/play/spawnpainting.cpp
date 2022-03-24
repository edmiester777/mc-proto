#include "spawnpainting.h"

namespace minecraft
{
    InboundSpawnPaintingPacket::InboundSpawnPaintingPacket(mcstream& stream)
    {
        stream >> *this;
    }

    int InboundSpawnPaintingPacket::entityId() const
    {
        return m_entityId;
    }

    int InboundSpawnPaintingPacket::paintingId() const
    {
        return m_paintingID;
    }

    uuid InboundSpawnPaintingPacket::entityUUID() const
    {
        return m_entityUUID;
    }

    position InboundSpawnPaintingPacket::location() const
    {
        return m_location;
    }

    PaintingDirection InboundSpawnPaintingPacket::direction() const
    {
        return m_dir;
    }

    string InboundSpawnPaintingPacket::to_string() const
    {
        string direction;
        switch (m_dir)
        {
        case PaintingDirection::NORTH:
            direction = "NORTH";
            break;
        case PaintingDirection::SOUTH:
            direction = "SOUTH";
            break;
        case PaintingDirection::EAST:
            direction = "EAST";
            break;
        case PaintingDirection::WEST:
            direction = "WEST";
            break;
        }

        stringstream s;
        s << endl
            << "\tid: " << m_entityId << endl
            << "\tuuid: " << m_entityUUID << endl
            << "\tlocation: " << m_location << " direction: " << direction << endl
            << "\tpaintingId: " << m_paintingID;

        return s.str();
    }

    mcstream& operator>>(mcstream& stream, InboundSpawnPaintingPacket& p)
    {
        varint entityId;
        varint motive;
        u8 direction;
        stream
            >> entityId
            >> p.m_entityUUID
            >> motive
            >> p.m_location
            >> direction;

        p.m_entityId = entityId.val();
        p.m_paintingID = motive.val();
        p.m_dir = (PaintingDirection)direction;

        return stream;
    }
}