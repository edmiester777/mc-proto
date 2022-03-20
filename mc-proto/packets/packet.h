#pragma once

#include "../inc.h"
#include "../nbt/nbt.h"

#define PACKET_IMPL(cls, state, packet_id) \
    public: \
        virtual std::string class_name() const override { return #cls; } \
        virtual std::string status_name() const override { return #state; } \
        virtual int id() const override { return (int)packet_id; } 

namespace minecraft
{
    class Packet
    {
    public:
        Packet() { }
        Packet(safebytebuffer& buffer) { }

        friend std::ostream& operator<<(std::ostream& stream, const Packet& packet);

        virtual int id() const { return -1; };
        
        safebytebuffer serialize() const;

        virtual string class_name() const { return "<UNIMPLEMENTED_PACKET>"; }
        virtual string status_name() const { return "<UNIMPLEMENTED_PACKET>"; }

        virtual string to_string() const;

    protected:
        virtual void serialize_data(safebytebuffer& buf) const;
    };
}