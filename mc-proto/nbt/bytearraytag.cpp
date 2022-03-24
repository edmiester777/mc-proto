#include "bytearraytag.h"

namespace minecraft
{
    NBTByteArrayTag::NBTByteArrayTag(mcstream& stream)
    {
        stream >> *this;
    }

    NBTByteArrayTag::NBTByteArrayTag(const vector<uint8_t>& value)
    {
        m_value = value;
    }

    void NBTByteArrayTag::operator=(const NBTByteArrayTag& other)
    {
        if (this != &other)
        {
            m_value = other.m_value;
        }
    }

    void NBTByteArrayTag::operator=(const vector<uint8_t>& value)
    {
        m_value = value;
    }

    size_t NBTByteArrayTag::size() const
    {
        return m_value.size();
    }

    uint8_t NBTByteArrayTag::operator[](int index) const
    {
        return m_value[index];
    }

    NBTTagTypes NBTByteArrayTag::type() const
    {
        return NBTTagTypes::TAG_BYTE_ARRAY;
    }

    void NBTByteArrayTag::write_data(mcstream& stream) const
    {
        i32 arrsize = (i32)size();
        stream << arrsize;
        for (int i = 0; i < arrsize; ++i)
        {
            stream << m_value[i];
        }
    }

    mcstream& operator>>(mcstream& stream, NBTByteArrayTag& tag)
    {
        i32 size;
        stream >> size;
        tag.m_value.resize(size);
        for (int i = 0; i < size; ++i)
        {
            u8 byte;
            stream >> byte;
            tag.m_value[i] = byte;
        }

        return stream;
    }
}
