#include "bytetag.h"
#include "tag.h"

minecraft::NBTByteTag::NBTByteTag(istream& data)
{
    // read single byte from stream
    data.read((char*)&m_byte, 1);
}

minecraft::NBTByteTag::NBTByteTag(uint8_t value)
{
    m_byte = value;
}

uint8_t minecraft::NBTByteTag::value() const
{
    return m_byte;
}

void minecraft::NBTByteTag::write(ostream& stream) const
{
    // write byte with tag prefix to stream
    uint8_t odata[2] = { NBTTagTypes::TAG_BYTE, m_byte };
    stream.write((char*)odata, 2);
}
