#include "position.h"
#include "inc.h"


namespace minecraft
{
    position::position()
        : m_x(0)
        , m_y(0)
        , m_z(0)
    {
    }

    position::position(int x, int y, int z)
        : m_x(x)
        , m_y(y)
        , m_z(z)
    {
    }

    int position::x() const
    {
        return m_x;
    }

    int position::y() const
    {
        return m_y;
    }

    int position::z() const
    {
        return m_z;
    }

#pragma warning(push)
#pragma warning(disable: 4244)
    mcstream& operator>>(mcstream& stream, position& pos)
    {
        u64 buf;
        stream >> buf;

        pos.m_x = buf >> 38;
        pos.m_y = buf & 0xFFF;
        pos.m_z = (buf >> 12) & 0x3FFFFFF;

        // adjusting for sign bit
        u64 bit = 1;
        if (pos.m_x >= bit << 25)
            pos.m_x -= bit << 26;
        if (pos.m_y >= bit << 11)
            pos.m_y -= bit << 12;
        if (pos.m_z >= bit << 25)
            pos.m_z -= bit << 26;

        return stream;
    }
#pragma warning(pop)

#pragma warning(push)
#pragma warning(disable: 4293)
    mcstream& operator<<(mcstream& stream, const position pos)
    {
        u64 data = ((pos.m_x & 0x3FFFFFF) << 38) | ((pos.m_z & 0x3FFFFFF) << 12) | (pos.m_y & 0xFFF);
        return stream << data;
    }
#pragma warning(pop)

    std::ostream& operator<<(std::ostream& stream, const position pos)
    {
        return stream
            << "(" << pos.m_x << ", " << pos.m_y << ", " << pos.m_z << ")";
    }
}