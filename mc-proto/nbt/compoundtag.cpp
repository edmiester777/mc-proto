#include "compoundtag.h"
#include "stringtag.h"
#include "bytetag.h"
#include <glog/logging.h>

using namespace minecraft;

minecraft::NBTCompoundTag::NBTCompoundTag(istream& stream)
{
    VLOG(VLOG_INFO) << "Starting parsing of TAG_COMPOUND";
    while (true)
    {
        // get type of next element
        uint8_t elementType = (NBTTagTypes)NBTByteTag(stream).value();

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

        m_value[nametag.value()] = valueTag;

        VLOG(VLOG_DEBUG)
            << "Read element \"" << nametag.value() << "\" "
               "with type " << elementType;
    }
}

minecraft::NBTCompoundTag::NBTCompoundTag(const map<string, NBTTagPtr>& value)
{
    m_value = value;
}

void minecraft::NBTCompoundTag::operator=(const NBTCompoundTag& other)
{
    if (this != &other)
    {
        m_value = other.m_value;
    }
}

void minecraft::NBTCompoundTag::operator=(const map<string, NBTTagPtr>& value)
{
    m_value = value;
}

NBTTagPtr& minecraft::NBTCompoundTag::operator[](const string& key)
{
    return m_value[key];
}

size_t minecraft::NBTCompoundTag::size() const
{
    return m_value.size();
}

bool minecraft::NBTCompoundTag::contains(const string& key)
{
    return m_value.contains(key);
}

NBTTagTypes minecraft::NBTCompoundTag::type() const
{
    return TAG_COMPOUND;
}

void minecraft::NBTCompoundTag::write_data(ostream& stream) const
{    
    map<string, NBTTagPtr>::iterator iter;
    for (iter = m_value.begin(); iter != m_value.end(); ++iter)
    {
        NBTByteTag((uint8_t)iter->second->type()).write_data(stream);
        NBTStringTag(iter->first).write_data(stream);
        iter->second->write_data(stream);
    }

    NBTByteTag((uint8_t)TAG_END).write_data(stream);
}
