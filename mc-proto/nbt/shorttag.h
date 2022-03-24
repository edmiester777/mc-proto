#pragma once

#include "../inc.h"
#include "tag.h"

namespace minecraft
{
    using namespace std;

    class NBTShortTag : public NBTTagBase
    {
    public:
        NBTShortTag(mcstream& stream);
        NBTShortTag(i16 val);
        void operator=(const NBTShortTag& other);
        void operator=(i16 value);

        int16_t value() const;

        virtual NBTTagTypes type() const override;
        virtual void write_data(mcstream& stream) const override;

        friend mcstream& operator>>(mcstream& stream, NBTShortTag& tag);

    private:
        i16 m_value;
    };
}
