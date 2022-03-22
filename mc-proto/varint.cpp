#include "varint.h"
#include "client.h"
#include <glog/logging.h>

namespace minecraft
{
    varint::varint()
        : m_value(0)
    {
    }
    varint::varint(int val)
        : m_value(val)
    {
    }

    varint::varint(function<uint8_t()> readFunc)
    {
        m_value = read(readFunc);
    }

    int varint::val() const
    {
        return m_value;
    }

    int varint::read(function<uint8_t()> readFunc)
    {
        unsigned int value = 0;
        int length = 0;
        uint8_t currentByte;

        while (true)
        {
            currentByte = readFunc();
            value |= (currentByte & 0x7F) << (length * 7);
        
            length += 1;
            if (length > 5)
            {
                LOG(WARNING) << "varint too long. max 5 bytes.";
                throw E_INVALID_PROTOCOL_FORMAT;
            }

            if ((currentByte & 0x80) != 0x80)
            {
                break;
            }
        }
        return value;
    }

    void varint::write(function<void(uint8_t)> writeFunc)
    {
        unsigned int value = m_value;
        while (true)
        {
            if ((value & ~0x7F) == 0)
            {
                writeFunc(value);
                return;
            }

            writeFunc((value & 0x7F) | 0x80);
            value >>= 7;
        }
    }

    mcstream& operator<<(mcstream& stream, varint& i)
    {
        i.write([&] (uint8_t b) {
            stream << b;
        });
        return stream;
    }

    mcstream& operator>>(mcstream& stream, varint& i)
    {
        int val = i.read([&] {
            uint8_t b;
            stream >> b;
            return b;
        });
        i.m_value = val;

        return stream;
    }
}