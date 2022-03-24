#include "bytearraytag.h"
#include "bytetag.h"
#include "inttag.h"

using namespace minecraft;

minecraft::NBTByteArrayTag::NBTByteArrayTag(istream& stream)
{
    int size = NBTIntTag(stream).value();
    for (int i = 0; i < size; ++i)
    {
        m_value.push_back(NBTByteTag(stream).value());
    }
}

minecraft::NBTByteArrayTag::NBTByteArrayTag(const vector<uint8_t>& value)
{
    m_value = value;
}

void minecraft::NBTByteArrayTag::operator=(const NBTByteArrayTag& other)
{
    if (this != &other)
    {
        m_value = other.m_value;
    }
}

void minecraft::NBTByteArrayTag::operator=(const vector<uint8_t>& value)
{
    m_value = value;
}

size_t minecraft::NBTByteArrayTag::size() const
{
    return m_value.size();
}

uint8_t minecraft::NBTByteArrayTag::operator[](int index) const
{
    return m_value[index];
}

NBTTagTypes minecraft::NBTByteArrayTag::type() const
{
    return NBTTagTypes::TAG_BYTE_ARRAY;
}

void minecraft::NBTByteArrayTag::write_data(ostream& stream) const
{
    NBTIntTag((int)size()).write_data(stream);
    for (int i = 0; i < size(); ++i)
    {
        NBTByteTag(m_value[i]).write_data(stream);
    }
}
