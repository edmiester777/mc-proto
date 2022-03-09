#pragma once
#include "../inc.h"
#include "tag.h"

namespace minecraft
{
    using namespace std;

    class NBTIntTag : public NBTTagBase
    {
    public:
        NBTIntTag(istream& stream);
        NBTIntTag(int val);
        void operator=(const NBTIntTag& other);
        void operator=(int32_t value);

        int32_t value();

        virtual NBTTagTypes type() const override;
        virtual void write_data(ostream& stream) const override;

    private:
        int32_t m_value;
    };
}