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

    Block::Block(int x, int y, int z, int type, shared_ptr<NBTCompoundTag> data)
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

    shared_ptr<NBTCompoundTag> Block::data() const
    {
        return m_data;
    }

    mcstream& operator>>(mcstream& stream, Block& b)
    {
        u8 xz;
        u16 y;
        stream >> xz >> y
            >> b.m_type;

        // unpacking x and z
        i8 xb = (xz >> 4) & 15;
        i8 zb = xz & 15;

        b.m_data = sp<NBTCompoundTag>(new NBTCompoundTag(stream));
        b.m_x = xb;
        b.m_y = y;
        b.m_z = zb;

        return stream;
    }

    std::ostream& operator<<(std::ostream& stream, Block& b)
    {
        // Ideally I'd like to have a nested print structure for when it is serialized
        // as a nested object, using something like indent_facet, but I don't have the
        // patience right now to do such a task.
        return stream << endl
            << "\t--------------------------------------------------------------"
            << "\tposition: (" << b.m_x << ", " << b.m_y << ", " << b.m_z << ")" << endl
            << "\ttype: " << b.m_type.val() << endl
            << "\tdata root tag name:" << b.m_data->name();
    }
}