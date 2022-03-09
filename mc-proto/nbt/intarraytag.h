#pragma once

#include "../inc.h"
#include "tag.h"

namespace minecraft
{
    class NBTIntArrayTag : public NBTTagBase
    {
    public:
        NBTIntArrayTag(istream& stream);
        NBTIntArrayTag(const vector<int32_t>& value);
        void operator=(const NBTIntArrayTag& other);
        void operator=(const vector<int32_t>& value);

        int32_t operator[](int index) const;
        size_t size() const;

        virtual NBTTagTypes type() const override;
        virtual void write_data(ostream& stream) const override;

    private:
        vector<int32_t> m_value;
    };
}