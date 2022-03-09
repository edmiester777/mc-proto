#pragma once

#include "bytetag.h"

namespace minecraft
{
    using namespace std;

    class NBTCompoundTag;
    typedef variant<NBTCompoundTag, NBTByteTag> NBTTag;

    class NBTCompoundTag
    {
    public:
        NBTCompoundTag(uint8_t* data, size_t len);
        NBTCompoundTag(const map<string, NBTTag> s);

        NBTCompoundTag& operator=(const NBTCompoundTag& other);
        NBTCompoundTag& operator=(const map<string, NBTTag>& children);
        NBTTag& operator[](const string& key);

        bool contains(const string& key);
    };
}