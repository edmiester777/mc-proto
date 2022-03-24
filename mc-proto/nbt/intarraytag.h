#pragma once

#include "../inc.h"
#include "tag.h"

namespace minecraft
{
    class NBTIntArrayTag : public NBTTagBase
    {
    public:
        NBTIntArrayTag(mcstream& stream);
        NBTIntArrayTag(const vector<i32>& value);
        void operator=(const NBTIntArrayTag& other);
        void operator=(const vector<i32>& value);

        int32_t operator[](int index) const;
        size_t size() const;

        virtual NBTTagTypes type() const override;
        virtual void write_data(mcstream& stream) const override;

        friend mcstream& operator>>(mcstream& stream, NBTIntArrayTag& arr);

    private:
        vector<i32> m_value;
    };
}