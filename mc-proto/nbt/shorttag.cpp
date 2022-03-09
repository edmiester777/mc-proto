#include "shorttag.h"

using namespace minecraft;

minecraft::NBTShortTag::NBTShortTag(istream& stream)
{
    int16_t buf;
    stream.read((char*)&buf, sizeof(int16_t));
    m_value = ntohs(buf);
}

minecraft::NBTShortTag::NBTShortTag(int16_t val)
{
    m_value = val;
}

void minecraft::NBTShortTag::operator=(const NBTShortTag& other)
{
    if (this != &other)
    {
        m_value = other.m_value;
    }
}

void minecraft::NBTShortTag::operator=(int16_t value)
{
    m_value = value;
}

int16_t minecraft::NBTShortTag::value() const
{
    return m_value;
}

void minecraft::NBTShortTag::write_data(ostream& stream) const
{
    int16_t outVal = htons(m_value);
    stream.write((char*)&outVal, sizeof(int16_t));
}

NBTTagTypes minecraft::NBTShortTag::type() const
{
    return NBTTagTypes::TAG_SHORT;
}
