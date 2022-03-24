#pragma once

#include "mcstream.h"

namespace minecraft
{
    /**
     *64-bit value split in to three parts
     * x: 26 MSBs
     * z: 26 middle bits
     * y: 12 LSBs
     * 
     * https://wiki.vg/Protocol#Position
     */
    struct position
    {
    public:
        position();
        position(int x, int y, int z);

        int x() const;
        int y() const;
        int z() const;
        
        friend mcstream& operator>>(mcstream& stream, position& pos);
        friend mcstream& operator<<(mcstream& stream, const position pos);
        friend std::ostream& operator<<(std::ostream& stream, const position pos);

    private:
        int m_x;
        int m_y;
        int m_z;
    };
}