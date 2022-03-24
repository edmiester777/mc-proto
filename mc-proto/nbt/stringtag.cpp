#include "stringtag.h"

namespace minecraft
{
    NBTStringTag::NBTStringTag(mcstream& stream)
    {
        stream >> *this;
    }

    NBTStringTag::NBTStringTag(string value)
    {
        m_value = value;
    }

    void NBTStringTag::operator=(const NBTStringTag& other)
    {
        if (this != &other)
        {
            m_value = other.m_value;
        }
    }

    void NBTStringTag::operator=(const string& value)
    {
        m_value = value;
    }

    string& NBTStringTag::value()
    {
        return m_value;
    }

    void NBTStringTag::write_data(mcstream& stream) const
    {
        u16 len = (u16)m_value.length();
        stream << len;
        stream.write(m_value.c_str(), len);
    }

    NBTTagTypes NBTStringTag::type() const
    {
        return NBTTagTypes::TAG_STRING;
    }

    mcstream& operator>>(mcstream& stream, NBTStringTag& tag)
    {
        u16 len;
        stream >> len;

        char* buf = new char[len];
        stream.read(buf, len);
        tag.m_value = string(buf, len);
        delete[] buf;

        return stream;
    }
}
