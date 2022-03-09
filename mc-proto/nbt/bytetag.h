#pragma once

#include "../inc.h"
#include "tag.h"

namespace minecraft
{
    using namespace std;
    class NBTByteTag : public NBTTagBase
    {
    public:
        NBTByteTag(istream& data);
        NBTByteTag(uint8_t value);

        uint8_t value() const;
        
        virtual void write(ostream& stream) const override;

    private:
        uint8_t m_byte;
    };
}