#pragma once

#include <vector>

namespace minecraft
{
    class mcstream;

    class bitset
    {
    public:
        bitset();
        bitset(mcstream& stream);

        uint64_t& operator[](const int index);
        size_t size() const;

        friend mcstream& operator>>(mcstream& stream, bitset& bs);
        friend mcstream& operator<<(mcstream& stream, const bitset& bs);

    private:
        std::vector<uint64_t> m_data;
    };
}