#include "bytetag.h"
#include "tag.h"

namespace minecraft
{
    NBTByteTag::NBTByteTag(mcstream& data)
    {
        // read single byte from stream
        data >> *this;
    }

    NBTByteTag::NBTByteTag(uint8_t value)
    {
        m_byte = value;
    }

    void NBTByteTag::operator=(const NBTByteTag& other)
    {
        if (this != &other)
        {
            m_byte = other.m_byte;
        }
    }

    void NBTByteTag::operator=(uint8_t value)
    {
        m_byte = value;
    }

    uint8_t NBTByteTag::value() const
    {
        return m_byte;
    }

    void NBTByteTag::write_data(mcstream& stream) const
    {
        stream << m_byte;
    }

    NBTTagTypes NBTByteTag::type() const
    {
        return NBTTagTypes::TAG_BYTE;
    }

    mcstream& operator>>(mcstream& stream, NBTByteTag& tag)
    {
        return stream >> tag.m_byte;
    }
}
