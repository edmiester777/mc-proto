#include "doubletag.h"

using namespace minecraft;

minecraft::NBTDoubleTag::NBTDoubleTag(istream& stream)
{
    uint64_t value;
    stream.read((char*)&value, sizeof(uint64_t));
    m_value = ntohd(value);
}

minecraft::NBTDoubleTag::NBTDoubleTag(double value)
{
    m_value = value;
}

void minecraft::NBTDoubleTag::operator=(const NBTDoubleTag& other)
{
    if (this != &other)
    {
        m_value = other.m_value;
    }
}

void minecraft::NBTDoubleTag::operator=(double value)
{
    m_value = value;
}

double minecraft::NBTDoubleTag::value() const
{
    return m_value;
}

void minecraft::NBTDoubleTag::write(ostream& stream) const
{
    uint8_t tagType = NBTTagTypes::TAG_DOUBLE;
    uint64_t networkValue = htond(m_value);

    stream.write((char*)&tagType, sizeof(uint8_t));
    stream.write((char*)&networkValue, sizeof(uint64_t));
}
