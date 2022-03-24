#pragma once

#include "../inc.h"
#include "tag.h"

namespace minecraft
{
    using namespace std;
    class NBTByteTag : public NBTTagBase
    {
    public:
        NBTByteTag(mcstream& data);
        NBTByteTag(uint8_t value);
        void operator=(const NBTByteTag& other);
        void operator=(uint8_t value);

        uint8_t value() const;
        
        virtual NBTTagTypes type() const override;
        virtual void write_data(mcstream& stream) const override;

        friend mcstream& operator>>(mcstream& stream, NBTByteTag& tag);

    private:
        uint8_t m_byte;
    };
}