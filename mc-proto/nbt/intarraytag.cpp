#include "intarraytag.h"

using namespace minecraft;

namespace minecraft
{
    NBTIntArrayTag::NBTIntArrayTag(mcstream& stream)
    {
        stream >> *this;
    }

    NBTIntArrayTag::NBTIntArrayTag(const vector<i32>& value)
    {
        m_value = value;
    }

    void NBTIntArrayTag::operator=(const NBTIntArrayTag& other)
    {
        if (this != &other)
        {
            m_value = other.m_value;
        }
    }

    void NBTIntArrayTag::operator=(const vector<i32>& value)
    {
        m_value = value;
    }

    int32_t NBTIntArrayTag::operator[](int index) const
    {
        return m_value[index];
    }

    size_t NBTIntArrayTag::size() const
    {
        return m_value.size();
    }

    NBTTagTypes NBTIntArrayTag::type() const
    {
        return NBTTagTypes::TAG_INT_ARRAY;
    }

    void NBTIntArrayTag::write_data(mcstream& stream) const
    {
        i32 size = (i32)m_value.size();
        stream << size;
        for (int i = 0; i < size; ++i)
        {
            stream << m_value[i];
        }
    }

    mcstream& operator>>(mcstream& stream, NBTIntArrayTag& arr)
    {
        i32 size;
        stream >> size;
        arr.m_value.resize(size);
        for (int i = 0; i < size; ++i)
        {
            i32 val;
            stream >> val;
            arr.m_value[i] = val;
        }

        return stream;
    }
}
