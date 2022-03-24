#pragma once

#include "../inc.h"
#include "tag.h"

namespace minecraft
{
    using namespace std;

    class NBTFloatTag : public NBTTagBase
    {
    public:
        NBTFloatTag(mcstream& stream);
        NBTFloatTag(float value);
        void operator=(const NBTFloatTag& other);
        void operator=(float value);

        float value() const;

        virtual NBTTagTypes type() const override;
        virtual void write_data(mcstream& stream) const override;

        friend mcstream& operator>>(mcstream& stream, NBTFloatTag& tag);

    private:
        float m_value;
    };
}