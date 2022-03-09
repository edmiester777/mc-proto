#pragma once
#include "../inc.h"
#include "tag.h"

namespace minecraft
{
    using namespace std;

    class NBTIntTag : NBTTagBase
    {
    public:
        NBTIntTag(istream& stream);
        NBTIntTag(int val);
        void operator=(const NBTIntTag& other);
        void operator=(int32_t value);

        int32_t value();

        virtual void write(ostream& stream) const override;

    private:
        int32_t m_value;
    };
}