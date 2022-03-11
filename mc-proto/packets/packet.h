#pragma once

#include "../inc.h"
#include "../nbt/nbt.h"

namespace minecraft
{
    class Packet
    {
    public:
        Packet(safebytebuffer buffer, size_t len) { }

        virtual int id() const;
        
        virtual safebytebuffer serializeData(size_t& bufferSize);
        virtual safebytebuffer serializeDataCompressed(size_t& bufferSize);

    private:
        int m_id;
        NBTTagPtr m_data;
    };
}