#pragma once

#include <sstream>
#include <string>

namespace minecraft
{
    using namespace std;

    class safebytebuffer;

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
        mcstream& operator>>(double& d);
        mcstream& operator>>(float& f);
        mcstream& operator>>(bool& v);
        mcstream& operator>>(string& s);
        mcstream& operator>>(safebytebuffer& buf);
        mcstream& operator<<(const int8_t v);
        mcstream& operator<<(const uint8_t v);
        mcstream& operator<<(const int16_t v);
        mcstream& operator<<(const uint16_t v);
        mcstream& operator<<(const int32_t v);
        mcstream& operator<<(const uint32_t v);
        mcstream& operator<<(const int64_t v);
        mcstream& operator<<(const uint64_t v);
        mcstream& operator<<(const double d);
        mcstream& operator<<(const float f);
        mcstream& operator<<(const bool v);
        mcstream& operator<<(const string v);
        mcstream& operator<<(const char* s);

        string read_string();
    };
}