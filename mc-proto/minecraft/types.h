#pragma once

#include "entitytypes.h"

namespace minecraft
{
    /**
     * ENUM representing the "Direction" byte field in InboundSpawnPaintingPacket
     */
    enum class PaintingDirection
    {
        SOUTH = 0,
        WEST = 1,
        NORTH = 2,
        EAST = 3,
    };
}