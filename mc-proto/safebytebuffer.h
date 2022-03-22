#pragma once

#include <vector>
#include <ostream>
#include <string>

namespace minecraft
{
    using namespace std;
    class varint;

    class safebytebuffer : public std::vector<std::uint8_t>
    {
    public:
        safebytebuffer() : std::vector<std::uint8_t>() { }
        safebytebuffer(const safebytebuffer& o) : std::vector<std::uint8_t>(o) { }

        safebytebuffer& operator<<(const bool b);
        safebytebuffer& operator<<(const uint8_t byte);
        safebytebuffer& operator<<(const int16_t s);
        safebytebuffer& operator<<(const uint16_t s);
        safebytebuffer& operator<<(const int32_t i);
        safebytebuffer& operator<<(const uint32_t i);
        safebytebuffer& operator<<(const int64_t l);
        safebytebuffer& operator<<(const uint64_t l);
        safebytebuffer& operator<<(const float f);
        safebytebuffer& operator<<(const double d);
        safebytebuffer& operator<<(const string& s);
        safebytebuffer& operator<<(const varint& i);

        friend std::ostream& operator<<(std::ostream& stream, const safebytebuffer& buf);

        void push_buffer(std::uint8_t* buf, size_t len);
        void push_stream(std::istream& stream);

        void push(bool b);
        void push(uint8_t byte);
        void push(int16_t s);
        void push(uint16_t s);
        void push(int32_t i);
        void push(uint32_t i);
        void push(int64_t l);
        void push(uint64_t l);
        void push(float f);
        void push(double d);
        void push(const string& s);
        void push(varint i);
    };
}