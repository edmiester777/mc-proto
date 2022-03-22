#pragma once

#include <sstream>
#include <string>

namespace minecraft
{
    using namespace std;

    class mcstream : public stringstream
    {
    public:
        mcstream() : stringstream() { }

        mcstream& operator>>(int8_t& v);
        mcstream& operator>>(uint8_t& v);
        mcstream& operator>>(int16_t& v);
        mcstream& operator>>(uint16_t& v);
        mcstream& operator>>(int32_t& v);
        mcstream& operator>>(uint32_t& v);
        mcstream& operator>>(int64_t& v);
        mcstream& operator>>(uint64_t& v);
        mcstream& operator>>(bool& v);
        mcstream& operator>>(string& s);
        mcstream& operator<<(int8_t& v);
        mcstream& operator<<(uint8_t& v);
        mcstream& operator<<(int16_t& v);
        mcstream& operator<<(uint16_t& v);
        mcstream& operator<<(int32_t& v);
        mcstream& operator<<(uint32_t& v);
        mcstream& operator<<(int64_t& v);
        mcstream& operator<<(uint64_t& v);
        mcstream& operator<<(bool& v);
        mcstream& operator<<(string& v);

        string read_string();
    };
}