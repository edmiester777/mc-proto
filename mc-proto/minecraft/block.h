#pragma once

#include "../inc.h"
#include "../nbt/nbt.h"

namespace minecraft
{
    class Block
    {
    public:
        Block();
        Block(int x, int y, int z, int type, NBTTagPtr data);
        Block(mcstream& stream);

        int x() const;
        int y() const;
        int z() const;
        int type() const;
        NBTTagPtr data() const;

        friend mcstream& operator>>(mcstream& stream, Block& b);
        friend std::ostream& operator<<(std::ostream& stream, const Block& b);

    private:
        int m_x;
        int m_y;
        int m_z;
        varint m_type;
        NBTTagPtr m_data;
    };
}