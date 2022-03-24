#include "inttag.h"

namespace minecraft
{
    NBTIntTag::NBTIntTag(mcstream& stream)
    {
        stream >> *this;
    }

    NBTIntTag::NBTIntTag(int val)
    {
        m_value = val;
    }

    void NBTIntTag::operator=(const NBTIntTag& other)
    {
        if (this != &other)
        {
            m_value = other.m_value;
        }
    }

    void NBTIntTag::operator=(int value)
    {
        m_value = value;
    }

    i32 NBTIntTag::value()
    {
        return m_value;
    }

    void NBTIntTag::write_data(mcstream& stream) const
    {
        stream << m_value;
    }

    NBTTagTypes NBTIntTag::type() const
    {
        return NBTTagTypes::TAG_INT;
    }

    mcstream& operator>>(mcstream& stream, NBTIntTag& tag)
    {
        return stream >> tag.m_value;
    }

}