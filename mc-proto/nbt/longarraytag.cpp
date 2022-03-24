#include "longarraytag.h"
#include "inttag.h"
#include "longtag.h"

using namespace minecraft;

minecraft::NBTLongArrayTag::NBTLongArrayTag(istream& stream)
{
    NBTIntTag size(stream);
    
    for (int i = 0; i < size.value(); ++i)
    {
        NBTLongTag val(stream);
        m_value.push_back(val.value());
    }
}

minecraft::NBTLongArrayTag::NBTLongArrayTag(const vector<int64_t>& value)
{
    m_value = value;
}

void minecraft::NBTLongArrayTag::operator=(const NBTLongArrayTag& other)
{
    if (this != &other)
    {
        m_value = other.m_value;
    }
}

void minecraft::NBTLongArrayTag::operator=(const vector<int64_t>& value)
{
    m_value = value;
}

size_t minecraft::NBTLongArrayTag::size()
{
    return m_value.size();
}

int64_t minecraft::NBTLongArrayTag::operator[](int index)
{
    return m_value[index];
}

NBTTagTypes minecraft::NBTLongArrayTag::type() const
{
    return NBTTagTypes::TAG_LONG_ARRAY;
}

void minecraft::NBTLongArrayTag::write_data(ostream& stream) const
{
    NBTIntTag((int)m_value.size()).write_data(stream);
    for (int i = 0; i < m_value.size(); ++i)
    {
        NBTLongTag(m_value[i]).write_data(stream);
    }
}
