#pragma once
#include "../inc.h"
#include "tag.h"

namespace minecraft
{
    class NBTLongArrayTag : public NBTTagBase
    {
    public:
        NBTLongArrayTag(mcstream& stream);
        NBTLongArrayTag(const vector<i64>& value);
        void operator=(const NBTLongArrayTag& other);
        void operator=(const vector<i64>& value);

        size_t size();
        i64& operator[](int index);

        virtual NBTTagTypes type() const override;
        virtual void write_data(mcstream& stream) const override;

        friend mcstream& operator>>(mcstream& stream, NBTLongArrayTag& tag);

    private:
        vector<int64_t> m_value;
    };
}