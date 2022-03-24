#pragma once

#include "../inc.h"
#include "tag.h"

namespace minecraft
{
    using namespace std;

    class NBTLongTag : public NBTTagBase
    {
    public:
        NBTLongTag(mcstream& stream);
        NBTLongTag(i64 value);
        void operator=(const NBTLongTag& other);
        void operator=(int64_t value);

        i64 value() const;

        virtual NBTTagTypes type() const override;
        virtual void write_data(mcstream& stream) const override;

        friend mcstream& operator>>(mcstream& stream, NBTLongTag& tag);

    private:
        i64 m_value;
    };
}