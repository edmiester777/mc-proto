#include "block.h"

namespace minecraft
{
    using namespace std;

    Block::Block()
        : m_x(0)
        , m_y(0)
        , m_z(0)
        , m_type(0)
        , m_data(nullptr)
    {
    }

    Block::Block(int x, int y, int z, int type, NBTTagPtr data)
        : m_x(x)
        , m_y(y)
        , m_z(z)
        , m_type(type)
        , m_data(data)
    {
    }

    Block::Block(mcstream& stream)
    {
        stream >> *this;
    }

    int Block::x() const
    {
        return m_x;
    }

    int Block::y() const
    {
        return m_y;
    }

    int Block::z() const
    {
        return m_z;
    }

    int Block::type() const
    {
        return m_type.val();
    }

    NBTTagPtr Block::data() const
    {
        return m_data;
    }

    mcstream& operator>>(mcstream& stream, Block& b)
    {
        u8 xz;
        u16 y;
        //stream >> xz >> y
        //    >> b.m_type;
        stream >> b.m_type;

        // unpacking x and z
        //u8 xb = (xz >> 4) & 15;
        //u8 zb = xz & 15;

        //b.m_data = sp<NBTCompoundTag>(new NBTCompoundTag(stream));
        b.m_data = read_nbt_from_stream(stream);
        //b.m_x = (int)xb;
        //b.m_y = (int)y;
        //b.m_z = (int)zb;

        return stream;
    }

    std::ostream& operator<<(std::ostream& stream, const Block& b)
    {
        // Ideally I'd like to have a nested print structure for when it is serialized
        // as a nested object, using something like indent_facet, but I don't have the
        // patience right now to do such a task.
        return stream << endl
            << "\tposition: (" << b.m_x << ", " << b.m_y << ", " << b.m_z << ")" << endl
            << "\ttype: " << b.m_type.val() << endl
            << "\tdata nbt type:" << (int)b.m_data->type();
    }
}