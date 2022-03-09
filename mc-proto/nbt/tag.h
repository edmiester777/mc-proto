#pragma once
#include "../inc.h"

namespace minecraft
{
    using namespace std;

    enum NBTTagTypes
    {
        TAG_END = 0,
        TAG_BYTE = 1,
        TAG_SHORT = 2,
        TAG_INT = 3,
        TAG_LONG = 4,
        TAG_FLOAT = 5,
        TAG_DOUBLE = 6,
        TAG_BYTE_ARRAY = 7,
        TAG_STRING = 8,
        TAG_LIST = 9,
        TAG_COMPOUND = 10,
        TAG_INT_ARRAY = 11,
        TAG_LONG_ARRAY = 12,
    };

    class NBTTagBase
    {
    public:
        virtual NBTTagTypes type() const = 0;
        void write(ostream& stream) const;
        virtual void write_data(ostream& stream) const = 0;
    };

    /**
     * Read a generic NBT from a stream. This includes loading the initial type
     * byte.
     */
    shared_ptr<NBTTagBase> read_nbt_from_stream(istream& stream);

    /**
     * Given a type, construct a generic NBT from a stream.
     */
    shared_ptr<NBTTagBase> read_nbt_from_stream_with_type(NBTTagTypes type, istream& stream);
}