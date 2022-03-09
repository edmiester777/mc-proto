#include "bytetag.h"
#include "tag.h"

using namespace minecraft;

minecraft::NBTByteTag::NBTByteTag(istream& data)
{
    // read single byte from stream
    data.read((char*)&m_byte, 1);
}

minecraft::NBTByteTag::NBTByteTag(uint8_t value)
{
    m_byte = value;
}

void minecraft::NBTByteTag::operator=(const NBTByteTag& other)
{
    if (this != &other)
    {
        m_byte = other.m_byte;
    }
}

void minecraft::NBTByteTag::operator=(uint8_t value)
{
    m_byte = value;
}

uint8_t minecraft::NBTByteTag::value() const
{
    return m_byte;
}

void minecraft::NBTByteTag::write_data(ostream& stream) const
{
    stream.write((char*)&m_byte, sizeof(uint8_t));
}

NBTTagTypes minecraft::NBTByteTag::type() const
{
    return NBTTagTypes::TAG_BYTE;
}
