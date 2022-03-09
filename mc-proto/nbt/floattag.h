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

        // Inherited via NBTTagBase
        virtual void write(ostream& stream) const override;

    private:
        float m_value;
    };
}