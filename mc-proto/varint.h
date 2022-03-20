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
        varint(int val);
        varint(function<uint8_t()> readFunc);

        friend std::ostream& operator<<(std::ostream& stream, minecraft::varint& i);
        friend std::istream& operator>>(std::istream& stream, minecraft::varint& i);

        int val() const;

        void write(function<void(uint8_t)> writeFunc);

    private:
        int read(function<uint8_t()> readFunc);

    private:
        int m_value;
    };
}