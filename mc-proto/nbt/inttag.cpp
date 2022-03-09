#include "inttag.h"

using namespace minecraft;

minecraft::NBTIntTag::NBTIntTag(istream& stream)
{
    int32_t networkValue;
    stream.read((char*)&networkValue, sizeof(int32_t));
    m_value = ntohl(networkValue);
}

minecraft::NBTIntTag::NBTIntTag(int val)
{
    m_value = val;
}

void minecraft::NBTIntTag::operator=(const NBTIntTag& other)
{
    if (this != &other)
    {
        m_value = other.m_value;
    }
}

void minecraft::NBTIntTag::operator=(int32_t value)
{
    m_value = value;
}

int32_t minecraft::NBTIntTag::value()
{
    return m_value;
}

void minecraft::NBTIntTag::write_data(ostream& stream) const
{
    int32_t networkValue = htonl(m_value);
    stream.write((char*)&networkValue, sizeof(int32_t));
}

NBTTagTypes minecraft::NBTIntTag::type() const
{
    return NBTTagTypes::TAG_INT;
}
