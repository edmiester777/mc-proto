#pragma once

#include "safebytebuffer.h"
#include "mcstream.h"
#include <functional>

namespace minecraft
{
    using namespace std;
    class varint
    {
    public:
        varint();
        varint(const varint& other);
        varint(int val);
        varint(function<uint8_t()> readFunc);

        friend mcstream& operator<<(mcstream& stream, varint i);
        friend mcstream& operator>>(mcstream& stream, varint& i);

        int val() const;

        void write(function<void(uint8_t)> writeFunc);

    private:
        int read(function<uint8_t()> readFunc);

    private:
        int m_value;
    };
}