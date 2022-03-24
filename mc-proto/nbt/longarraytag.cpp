#include "longarraytag.h"
#include "inttag.h"
#include "longtag.h"

namespace minecraft
{
    NBTLongArrayTag::NBTLongArrayTag(mcstream& stream)
    {
        stream >> *this;
    }

    NBTLongArrayTag::NBTLongArrayTag(const vector<i64>& value)
    {
        m_value = value;
    }

    void NBTLongArrayTag::operator=(const NBTLongArrayTag& other)
    {
        if (this != &other)
        {
            m_value = other.m_value;
        }
    }

    void NBTLongArrayTag::operator=(const vector<i64>& value)
    {
        m_value = value;
    }

    size_t NBTLongArrayTag::size()
    {
        return m_value.size();
    }

    i64& NBTLongArrayTag::operator[](int index)
    {
        return m_value[index];
    }

    NBTTagTypes NBTLongArrayTag::type() const
    {
        return NBTTagTypes::TAG_LONG_ARRAY;
    }

    void NBTLongArrayTag::write_data(mcstream& stream) const
    {
        i32 size = (i32)m_value.size();
        stream << size;
        for (int i = 0; i < size; ++i)
        {
            stream << m_value[i];
        }
    }

    mcstream& operator>>(mcstream& stream, NBTLongArrayTag& tag)
    {
        i32 size;
        stream >> size;
        tag.m_value.resize(size);

        for (int i = 0; i < size; ++i)
        {
            i64 val;
            stream >> val;
            tag.m_value[i] = val;
        }

        return stream;
    }
}
