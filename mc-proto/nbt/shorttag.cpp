#include "shorttag.h"

namespace minecraft
{
    NBTShortTag::NBTShortTag(mcstream& stream)
    {
        stream >> *this;
    }

    NBTShortTag::NBTShortTag(i16 val)
    {
        m_value = val;
    }

    void NBTShortTag::operator=(const NBTShortTag& other)
    {
        if (this != &other)
        {
            m_value = other.m_value;
        }
    }

    void NBTShortTag::operator=(i16 value)
    {
        m_value = value;
    }

    int16_t NBTShortTag::value() const
    {
        return m_value;
    }

    void NBTShortTag::write_data(mcstream& stream) const
    {
        stream << m_value;
    }

    NBTTagTypes NBTShortTag::type() const
    {
        return NBTTagTypes::TAG_SHORT;
    }

    mcstream& operator>>(mcstream& stream, NBTShortTag& tag)
    {
        return stream >> tag.m_value;
    }

}
