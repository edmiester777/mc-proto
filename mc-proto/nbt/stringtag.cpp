#include "stringtag.h"
#include "shorttag.h"

using namespace minecraft;

minecraft::NBTStringTag::NBTStringTag(istream& stream)
{
    // first find the length of this string
    NBTShortTag lengthTag(stream);

    // read string of this length into buffer
    char* rawstr = new char[lengthTag.value()];
    stream.read(rawstr, lengthTag.value());

    // strings from NBT streams are not null-termintated. We must construct
    // it with an exact size.
    m_value = string(rawstr, lengthTag.value());
}

minecraft::NBTStringTag::NBTStringTag(string value)
{
    m_value = value;
}

void minecraft::NBTStringTag::operator=(const NBTStringTag& other)
{
    if (this != &other)
    {
        m_value = other.m_value;
    }
}

void minecraft::NBTStringTag::operator=(const string& value)
{
    m_value = value;
}

string& minecraft::NBTStringTag::value()
{
    return m_value;
}

void minecraft::NBTStringTag::write(ostream& stream) const
{
    uint8_t tagType = NBTTagTypes::TAG_STRING;
    uint16_t length = htons(m_value.length());
    stream.write((char*)&tagType, sizeof(uint8_t));
    stream.write((char*)&length, sizeof(uint16_t));
    stream.write(m_value.c_str(), m_value.length());
}
