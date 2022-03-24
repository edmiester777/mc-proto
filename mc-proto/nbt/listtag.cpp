#include "listtag.h"
#include "tag.h"
#include "bytetag.h"
#include "inttag.h"

namespace minecraft
{
    NBTListTag::NBTListTag(mcstream& stream)
    {
        NBTByteTag type(stream);
        NBTIntTag size(stream);

        m_elementType = (NBTTagTypes)type.value();

        for (int i = 0; i < size.value(); ++i)
        {
            m_value.push_back(read_nbt_from_stream_with_type(m_elementType, stream));
        }
    }

    NBTListTag::NBTListTag(const NBTTagTypes type, const vector<NBTTagPtr>& value)
    {
        m_elementType = type;
        m_value = value;
    }

    void NBTListTag::operator=(const NBTListTag& other)
    {
        if (this != &other)
        {
            m_elementType = other.m_elementType;
            m_value = other.m_value;
        }
    }

    NBTTagPtr& NBTListTag::operator[](int index)
    {
        return m_value[index];
    }

    vector<NBTTagPtr>& NBTListTag::value()
    {
        return m_value;
    }

    size_t NBTListTag::size() const
    {
        return m_value.size();
    }

    NBTTagTypes NBTListTag::elementType() const
    {
        return m_elementType;
    }

    NBTTagTypes NBTListTag::type() const
    {
        return TAG_LIST;
    }

    void NBTListTag::write_data(mcstream& stream) const
    {
        NBTByteTag((uint8_t)m_elementType).write_data(stream);
        NBTIntTag((int)size()).write_data(stream);
        for (int i = 0; i < size(); ++i)
        {
            m_value[i]->write_data(stream);
        }
    }

    mcstream& operator>>(mcstream& stream, NBTListTag& tag)
    {
        u8 etype;
        i32 size;
        stream >> etype >> size;

        tag.m_elementType = (NBTTagTypes)etype;

        tag.m_value.resize(size);
        for (int i = 0; i < size; ++i)
        {
            tag.m_value[i] = read_nbt_from_stream_with_type(tag.m_elementType, stream);
        }

        return stream;
    }

}