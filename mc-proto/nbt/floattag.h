#pragma once

#include "../inc.h"
#include "tag.h"

namespace minecraft
{
    using namespace std;

    class NBTFloatTag : public NBTTagBase
    {
    public:
        NBTFloatTag(istream& stream);
        NBTFloatTag(float value);
        void operator=(const NBTFloatTag& other);
        void operator=(float value);

        float value() const;

        virtual NBTTagTypes type() const override;
        virtual void write_data(ostream& stream) const override;

    private:
        float m_value;
    };
}