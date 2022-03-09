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

    // cleanup
    delete[] rawstr;
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

void minecraft::NBTStringTag::write_data(ostream& stream) const
{
    // writing string length
    NBTShortTag(m_value.length()).write_data(stream);

    // writing our data
    stream.write(m_value.c_str(), m_value.length());
}

NBTTagTypes minecraft::NBTStringTag::type() const
{
    return NBTTagTypes::TAG_STRING;
}
