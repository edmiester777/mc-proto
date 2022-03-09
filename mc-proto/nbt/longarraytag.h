#pragma once
#include "../inc.h"
#include "tag.h"

namespace minecraft
{
    class NBTLongArrayTag : public NBTTagBase
    {
    public:
        NBTLongArrayTag(istream& stream);
        NBTLongArrayTag(const vector<int64_t>& value);
        void operator=(const NBTLongArrayTag& other);
        void operator=(const vector<int64_t>& value);

        size_t size();
        int64_t operator[](int index);

        virtual NBTTagTypes type() const override;
        virtual void write_data(ostream& stream) const override;

    private:
        vector<int64_t> m_value;
    };
}