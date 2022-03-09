#pragma once

#include "../inc.h"
#include "tag.h"

namespace minecraft
{
    using namespace std;

    class NBTShortTag : public NBTTagBase
    {
    public:
        NBTShortTag(istream& stream);
        NBTShortTag(int16_t val);
        void operator=(const NBTShortTag& other);
        void operator=(int16_t value);

        int16_t value() const;

        virtual void write(ostream& stream) const override;

    private:
        int16_t m_value;
    };
}
