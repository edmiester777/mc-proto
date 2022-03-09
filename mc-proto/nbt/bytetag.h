#pragma once

#include "../inc.h"

namespace minecraft
{
    using namespace std;
    class NBTByteTag
    {
    public:
        NBTByteTag(istream& data);
        NBTByteTag(uint8_t value);

        uint8_t value() const;
        
        void write(ostream& stream);

    private:
        uint8_t m_byte;
    };
}