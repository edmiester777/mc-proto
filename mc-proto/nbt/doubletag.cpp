#include "doubletag.h"

namespace minecraft
{
    NBTDoubleTag::NBTDoubleTag(mcstream& stream)
    {
        stream >> *this;
    }

    NBTDoubleTag::NBTDoubleTag(double value)
    {
        m_value = value;
    }

    void NBTDoubleTag::operator=(const NBTDoubleTag& other)
    {
        if (this != &other)
        {
            m_value = other.m_value;
        }
    }

    void NBTDoubleTag::operator=(double value)
    {
        m_value = value;
    }

    double NBTDoubleTag::value() const
    {
        return m_value;
    }

    void NBTDoubleTag::write_data(mcstream& stream) const
    {
        stream << m_value;
    }

    NBTTagTypes NBTDoubleTag::type() const
    {
        return NBTTagTypes::TAG_DOUBLE;
    }

    mcstream& operator>>(mcstream& stream, NBTDoubleTag& tag)
    {
        return stream >> tag.m_value;
    }

}