#pragma once

#include "../inc.h"

namespace minecraft
{
    using namespace std;

    class PacketObject
    {
    public:
        PacketObject(istream datastream);

        virtual void from_nbt(nbt::NBT& data) = 0;
        virtual nbt::NBT to_nbt() = 0;
        virtual int packet_id() = 0;
    };
}