#pragma once

#include "../inc.h"
#include "../nbt/nbt.h"

namespace minecraft
{
    class Packet
    {
    public:
        Packet() { }
        Packet(safebytebuffer& buffer) { }

        virtual int id() const = 0;
        
        safebytebuffer serialize() const;

    protected:
        virtual void serialize_data(safebytebuffer& buf) const = 0;
    };
}