#include "compoundtag.h"
#include "stringtag.h"
#include "bytetag.h"
#include <glog/logging.h>

namespace minecraft
{
    NBTCompoundTag::NBTCompoundTag(mcstream& stream)
    {
        stream >> *this;
    }

    NBTCompoundTag::NBTCompoundTag(const string& name, const map<string, NBTTagPtr>& value)
        : m_name(name)
        , m_value(value)
    {
    }

    void NBTCompoundTag::operator=(const NBTCompoundTag& other)
    {
        if (this != &other)
        {
            m_value = other.m_value;
        }
    }

    void NBTCompoundTag::operator=(const map<string, NBTTagPtr>& value)
    {
        m_value = value;
    }

    NBTTagPtr& NBTCompoundTag::operator[](const string& key)
    {
        return m_value[key];
    }

    size_t NBTCompoundTag::size() const
    {
        return m_value.size();
    }

    bool NBTCompoundTag::contains(const string& key) const
    {
        return m_value.contains(key);
    }

    string NBTCompoundTag::name() const
    {
        return m_name;
    }

    NBTTagTypes NBTCompoundTag::type() const
    {
        return TAG_COMPOUND;
    }

    void NBTCompoundTag::write_data(mcstream& stream) const
    {
        NBTStringTag(m_name).write_data(stream);
        map<string, NBTTagPtr>::iterator iter;
        for (iter = m_value.begin(); iter != m_value.end(); ++iter)
        {
            NBTByteTag((u8)iter->second->type()).write_data(stream);
            NBTStringTag(iter->first).write_data(stream);
            iter->second->write_data(stream);
        }

        NBTByteTag((u8)TAG_END).write_data(stream);
    }

    mcstream& operator>>(mcstream& stream, NBTCompoundTag& t)
    {
        VLOG(VLOG_DEBUG) << "Starting parsing of TAG_COMPOUND";
        NBTStringTag pname(stream);
        t.m_name = pname.value();

        while (true)
        {
            // get type of next element
            u8 elementType;
            stream >> elementType;

            // COMPOUND_END signifies the end of this object
            if (elementType == TAG_END)
            {
                VLOG(VLOG_DEBUG) << "Reached end of compound.";
                break;
            }

            // get the name of the element
            NBTStringTag nametag(stream);

            // get the value of this element
            NBTTagPtr valueTag = read_nbt_from_stream_with_type((NBTTagTypes)elementType, stream);

            t.m_value[nametag.value()] = valueTag;

            VLOG(VLOG_DEBUG)
                << "Read element \"" << nametag.value() << "\" "
                "with type " << elementType;

        }
        return stream;
    }
}
