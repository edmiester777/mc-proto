#include "floattag.h"

namespace minecraft
{
    NBTFloatTag::NBTFloatTag(mcstream& stream)
    {
        stream >> *this;
    }

    NBTFloatTag::NBTFloatTag(float value)
    {
        m_value = value;
    }

    void NBTFloatTag::operator=(const NBTFloatTag& other)
    {
        if (this != &other)
        {
            m_value = other.m_value;
        }
    }

    void NBTFloatTag::operator=(float value)
    {
        m_value = value;
    }

    float NBTFloatTag::value() const
    {
        return m_value;
    }

    void NBTFloatTag::write_data(mcstream& stream) const
    {
        stream << m_value;
    }

    NBTTagTypes NBTFloatTag::type() const
    {
        return NBTTagTypes::TAG_FLOAT;
    }

    mcstream& operator>>(mcstream& stream, NBTFloatTag& tag)
    {
        return stream >> tag.m_value;
    }
}