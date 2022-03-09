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

int16_t minecraft::NBTShortTag::value() const
{
    return m_value;
}

void minecraft::NBTShortTag::write(ostream& stream) const
{
    uint8_t tagType = NBTTagTypes::TAG_SHORT;
    stream.write((char*)&tagType, sizeof(uint8_t));
    int16_t outVal = htons(m_value);
    stream.write((char*)&outVal, sizeof(int16_t));
}
