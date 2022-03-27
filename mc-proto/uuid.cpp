#include "uuid.h"
#include <sstream>
#include <iomanip>
#include <glog/logging.h>

namespace minecraft
{
    uint8_t hex2byte(char c)
    {
        if (between(c, '0', '9'))
        {
            return c - '0';
        }
        if (between(c, 'a', 'f'))
        {
            return (c - 'a') + 10;
        }
        if (between(c, 'A', 'F'))
        {
            return (c - 'A') + 10;
        }

        return 0;
    }

    uuid::uuid()
        : m_mostSignificant(0)
        , m_leastSignificant(0)
    {
    }

    uuid::uuid(uint64_t ms, uint64_t ls)
        : m_mostSignificant(ms)
        , m_leastSignificant(ls)
    {
    }

    uuid::uuid(string& s)
    {
        char chars[32];
        
        int p = 0;
        for (int i = 0; i < s.length(); ++i)
        {
            if (s[i] == '-')
                continue;

            chars[p++] = s[i];
        }

        uint8_t bytes[16];

        for (int i = 0; i < 16; ++i)
        {
            bytes[i] = (hex2byte(chars[i * 2]) << 4) | hex2byte(chars[(i * 2) + 1]);
        }

        memcpy(&m_mostSignificant, bytes, 8);
        memcpy(&m_leastSignificant, bytes + 8, 8);
    }

    string uuid::to_string() const
    {
        uint8_t bytes[16];
        memcpy(bytes, &m_mostSignificant, 8);
        memcpy(bytes + 8, &m_leastSignificant, 8);

        stringstream sstream;
        for (int i = 0; i < 4; ++i)
            sstream << hex << setw(2) << setfill('0') << (int)bytes[i];

        sstream << '-';
        sstream << hex << setw(2) << setfill('0') << (int)bytes[4];
        sstream << hex << setw(2) << setfill('0') << (int)bytes[5];
        sstream << '-';
        sstream << hex << setw(2) << setfill('0') << (int)bytes[6];
        sstream << hex << setw(2) << setfill('0') << (int)bytes[7];
        sstream << '-';
        sstream << hex << setw(2) << setfill('0') << (int)bytes[8];
        sstream << hex << setw(2) << setfill('0') << (int)bytes[9];
        sstream << '-';

        for (int i = 10; i < 16; ++i)
            sstream << hex << setw(2) << setfill('0') << (int)bytes[i];

        return sstream.str();
    }

    mcstream& operator>>(mcstream& stream, uuid& u)
    {
        stream >> u.m_mostSignificant >> u.m_leastSignificant;
        return stream;
    }

    mcstream& operator<<(mcstream& stream, const uuid& u)
    {
        stream << u.m_mostSignificant << u.m_leastSignificant;
        return stream;
    }

    std::ostream& operator<<(std::ostream& stream, const minecraft::uuid& u)
    {
        stream << u.to_string();
        return stream;
    }
}
