#include "intarraytag.h"
#include "inttag.h"

using namespace minecraft;

minecraft::NBTIntArrayTag::NBTIntArrayTag(istream& stream)
{
    NBTIntTag lengthTag(stream);

    for (int i = 0; i < lengthTag.value(); ++i)
    {
        NBTIntTag indexTag(stream);
        m_value.push_back(indexTag.value());
    }
}

minecraft::NBTIntArrayTag::NBTIntArrayTag(const vector<int32_t>& value)
{
    m_value = value;
}

void minecraft::NBTIntArrayTag::operator=(const NBTIntArrayTag& other)
{
    if (this != &other)
    {
        m_value = other.m_value;
    }
}

void minecraft::NBTIntArrayTag::operator=(const vector<int32_t>& value)
{
    m_value = value;
}

int32_t minecraft::NBTIntArrayTag::operator[](int index) const
{
    return m_value[index];
}

size_t minecraft::NBTIntArrayTag::size() const
{
    return m_value.size();
}

NBTTagTypes minecraft::NBTIntArrayTag::type() const
{
    return NBTTagTypes::TAG_INT_ARRAY;
}

void minecraft::NBTIntArrayTag::write_data(ostream& stream) const
{
    NBTIntTag((int)size()).write_data(stream);

    for (int i = 0; i < m_value.size(); ++i)
    {
        NBTIntTag(m_value[i]).write_data(stream);
    }
}
