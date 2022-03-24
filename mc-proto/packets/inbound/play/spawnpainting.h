#pragma once

#include "../../packet.h"
#include "../../states.h"
#include "../../../minecraft/types.h"

namespace minecraft
{
    class InboundSpawnPaintingPacket : public Packet
    {
        PACKET_IMPL(InboundSpawnPaintingPacket, States::PLAY, PlayPacketIds::I_SPAWN_PAINTING)
    public:
        InboundSpawnPaintingPacket(mcstream& stream);

        int entityId() const;
        int paintingId() const;
        uuid uid() const;
        position location() const;
        PaintingDirection direction() const;

        string to_string() const override;

        friend mcstream& operator>>(mcstream& stream, InboundSpawnPaintingPacket& p);

    private:
        int m_entityId;
        int m_paintingID; // Motive of painting
        uuid m_entityUUID;
        position m_location;
        PaintingDirection m_dir;
    };
}