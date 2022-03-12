#pragma once

#include <vector>
#include <ostream>
#include <string>

namespace minecraft
{
    using namespace std;

    class safebytebuffer : public std::vector<std::uint8_t>
    {
    public:
        safebytebuffer() : std::vector<std::uint8_t>() { }
        safebytebuffer(const safebytebuffer& o) : std::vector<std::uint8_t>(o) { }

        std::ostream& operator<<(std::ostream& stream) const;

        void push_buffer(std::uint8_t* buf, size_t len);
        void push_stream(std::istream& stream);

        void write(bool b);
        void write(uint8_t byte);
        void write(int16_t s);
        void write(uint16_t s);
        void write(int32_t i);
        void write(uint32_t i);
        void write(int64_t l);
        void write(uint64_t l);
        void write(float f);
        void write(double d);
        void write(string s);
        void writeVarInt(int i);
    };
}