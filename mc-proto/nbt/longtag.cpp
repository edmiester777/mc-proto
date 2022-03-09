#include "longtag.h"

using namespace minecraft;

minecraft::NBTLongTag::NBTLongTag(istream& stream)
{
    int64_t networkVal;
    stream.read((char*)&networkVal, sizeof(int64_t));
    m_value = ntohll(networkVal);
}

minecraft::NBTLongTag::NBTLongTag(int64_t value)
{
    m_value = value;
}

void minecraft::NBTLongTag::operator=(const NBTLongTag& other)
{
    if (this != &other)
    {
        m_value = other.m_value;
    }
}

void minecraft::NBTLongTag::operator=(int64_t value)
{
    m_value = value;
}

int64_t minecraft::NBTLongTag::value() const
{
    return m_value;
}

void minecraft::NBTLongTag::write(ostream& stream) const
{
    uint8_t tagType = NBTTagTypes::TAG_LONG;
    int64_t networkValue = htonll(m_value);
    stream.write((char*)&tagType, sizeof(uint8_t));
    stream.write((char*)&networkValue, sizeof(int64_t));
}
