#include "floattag.h"

using namespace minecraft;

minecraft::NBTFloatTag::NBTFloatTag(istream& stream)
{
    uint32_t networkValue;
    stream.read((char*)&networkValue, sizeof(uint32_t));
    m_value = ntohf(networkValue);
}

minecraft::NBTFloatTag::NBTFloatTag(float value)
{
    m_value = value;
}

void minecraft::NBTFloatTag::operator=(const NBTFloatTag& other)
{
    if (this != &other)
    {
        m_value = other.m_value;
    }
}

void minecraft::NBTFloatTag::operator=(float value)
{
    m_value = value;
}

float minecraft::NBTFloatTag::value() const
{
    return m_value;
}

void minecraft::NBTFloatTag::write_data(ostream& stream) const
{
    uint32_t networkValue = htonf(m_value);
    stream.write((char*)&networkValue, sizeof(uint32_t));
}

NBTTagTypes minecraft::NBTFloatTag::type() const
{
    return NBTTagTypes::TAG_FLOAT;
}
