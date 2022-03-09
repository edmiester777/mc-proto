#pragma once

#include "../inc.h"
#include "tag.h"

namespace minecraft
{
    using namespace std;

    class NBTLongTag : public NBTTagBase
    {
    public:
        NBTLongTag(istream& stream);
        NBTLongTag(int64_t value);
        void operator=(const NBTLongTag& other);
        void operator=(int64_t value);

        int64_t value() const;

        virtual void write(ostream& stream) const override;

    private:
        int64_t m_value;
    };
}