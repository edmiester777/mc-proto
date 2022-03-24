#include "longtag.h"

namespace minecraft
{
    NBTLongTag::NBTLongTag(mcstream& stream)
    {
        stream >> *this;
    }

    NBTLongTag::NBTLongTag(i64 value)
    {
        m_value = value;
    }

    void NBTLongTag::operator=(const NBTLongTag& other)
    {
        if (this != &other)
        {
            m_value = other.m_value;
        }
    }

    void NBTLongTag::operator=(int64_t value)
    {
        m_value = value;
    }

    int64_t NBTLongTag::value() const
    {
        return m_value;
    }

    void NBTLongTag::write_data(mcstream& stream) const
    {
        stream << m_value;
    }

    NBTTagTypes NBTLongTag::type() const
    {
        return NBTTagTypes::TAG_LONG;
    }

    mcstream& operator>>(mcstream& stream, NBTLongTag& tag)
    {
        return stream >> tag.m_value;
    }
}
