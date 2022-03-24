#include "listtag.h"
#include "tag.h"
#include "bytetag.h"
#include "inttag.h"

using namespace minecraft;

minecraft::NBTListTag::NBTListTag(istream& stream)
{
    NBTByteTag type(stream);
    NBTIntTag size(stream);

    m_elementType = (NBTTagTypes)type.value();

    for (int i = 0; i < size.value(); ++i)
    {
        m_value.push_back(read_nbt_from_stream_with_type(m_elementType, stream));
    }
}

minecraft::NBTListTag::NBTListTag(const NBTTagTypes type, const vector<NBTTagPtr>& value)
{
    m_elementType = type;
    m_value = value;
}

void minecraft::NBTListTag::operator=(const NBTListTag& other)
{
    if (this != &other)
    {
        m_elementType = other.m_elementType;
        m_value = other.m_value;
    }
}

NBTTagPtr& minecraft::NBTListTag::operator[](int index)
{
    return m_value[index];
}

vector<NBTTagPtr>& minecraft::NBTListTag::value()
{
    return m_value;
}

size_t minecraft::NBTListTag::size() const
{
    return m_value.size();
}

NBTTagTypes minecraft::NBTListTag::elementType() const
{
    return m_elementType;
}

NBTTagTypes minecraft::NBTListTag::type() const
{
    return TAG_LIST;
}

void minecraft::NBTListTag::write_data(ostream& stream) const
{
    NBTByteTag((uint8_t)m_elementType).write_data(stream);
    NBTIntTag((int)size()).write_data(stream);
    for (int i = 0; i < size(); ++i)
    {
        m_value[i]->write_data(stream);
    }
}
