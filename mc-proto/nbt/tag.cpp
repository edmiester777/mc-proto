#include "tag.h"
#include "nbt.h"
#include "glog/logging.h"

#define CHECK_CONSTRUCT_TAG_TYPE(tagtype, clstype, stream) \
    case tagtype: \
        return NBTTagPtr(new clstype(stream)); \
        break;

namespace minecraft
{
    void NBTTagBase::write(mcstream& stream) const
    {
        // we have to write the type byte first
        uint8_t type = this->type();
        stream.write((char*)&type, sizeof(uint8_t));

        // write the rest of our content
        this->write_data(stream);
    }

    mcstream& operator<<(mcstream& stream, NBTTagBase& tag)
    {
        throw E_NOTIMPL;
        tag.write(stream);
        return stream;
    }

    NBTTagPtr read_nbt_from_stream(mcstream& stream)
    {
        // each tag is prefixed with a type. figure out which type it is
        uint8_t tagType;
        stream >> tagType;

        // now that we have the type, we can convert it to the NBT
        return read_nbt_from_stream_with_type((NBTTagTypes)tagType, stream);
    }

    NBTTagPtr read_nbt_from_stream_with_type(NBTTagTypes type, mcstream& stream)
    {
        switch (type)
        {
            CHECK_CONSTRUCT_TAG_TYPE(TAG_BYTE_ARRAY, NBTByteArrayTag, stream)
            CHECK_CONSTRUCT_TAG_TYPE(TAG_BYTE, NBTByteTag, stream)
            CHECK_CONSTRUCT_TAG_TYPE(TAG_COMPOUND, NBTCompoundTag, stream)
            CHECK_CONSTRUCT_TAG_TYPE(TAG_DOUBLE, NBTDoubleTag, stream)
            CHECK_CONSTRUCT_TAG_TYPE(TAG_FLOAT, NBTFloatTag, stream)
            CHECK_CONSTRUCT_TAG_TYPE(TAG_INT_ARRAY, NBTIntArrayTag, stream)
            CHECK_CONSTRUCT_TAG_TYPE(TAG_INT, NBTIntTag, stream)
            CHECK_CONSTRUCT_TAG_TYPE(TAG_LIST, NBTListTag, stream)
            CHECK_CONSTRUCT_TAG_TYPE(TAG_LONG_ARRAY, NBTLongArrayTag, stream)
            CHECK_CONSTRUCT_TAG_TYPE(TAG_LONG, NBTLongTag, stream)
            CHECK_CONSTRUCT_TAG_TYPE(TAG_SHORT, NBTShortTag, stream)
            CHECK_CONSTRUCT_TAG_TYPE(TAG_STRING, NBTStringTag, stream)
        default:
            LOG(WARNING)
                << "Tried to parse invalid tag type (" << type << ")";
            throw invalid_argument("Tag type was invalid.");
        }
    }
}