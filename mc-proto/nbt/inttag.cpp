#include "inttag.h"

using namespace std;

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

int32_t minecraft::NBTIntTag::value()
{
    return m_value;
}

void minecraft::NBTIntTag::write(ostream& stream) const
{
    uint8_t tagType = NBTTagTypes::TAG_INT;
    int32_t networkValue = htonl(m_value);
    stream.write((char*)&tagType, sizeof(uint8_t));
    stream.write((char*)&networkValue, sizeof(int32_t));
}
