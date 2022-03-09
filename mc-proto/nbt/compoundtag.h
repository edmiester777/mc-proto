#pragma once

#include "../inc.h"
#include "tag.h"

namespace minecraft
{
    using namespace std;

    class NBTCompoundTag : public NBTTagBase
    {
    public:
        NBTCompoundTag(istream& stream);
        NBTCompoundTag(const map<string, shared_ptr<NBTTagBase>> s);

        NBTCompoundTag& operator=(const NBTCompoundTag& other);
        NBTCompoundTag& operator=(const map<string, shared_ptr<NBTTagBase>>& children);
        shared_ptr<NBTTagBase>& operator[](const string& key);

        bool contains(const string& key);

        virtual NBTTagTypes type() const override;
        virtual void write_data(ostream& stream) const override;
    };
}