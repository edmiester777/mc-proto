#include "bitset.h"
#include "inc.h"

namespace minecraft
{
    bitset::bitset()
    {
    }

    bitset::bitset(mcstream& stream)
    {
        stream >> *this;
    }

    uint64_t& bitset::operator[](const int index)
    {
        return m_data[index];
    }

    size_t bitset::size() const
    {
        return m_data.size();
    }

    mcstream& operator>>(mcstream& stream, bitset& bs)
    {
        varint size;
        stream >> size;
        bs.m_data.resize(size.val());

        for (int i = 0; i < size.val(); ++i)
        {
            u64 v;
            stream >> v;
            bs.m_data[i] = v;
        }

        return stream;
    }

    mcstream& operator<<(mcstream& stream, const bitset& bs)
    {
        stream << varint(bs.m_data.size());

        for (int i = 0; i < bs.m_data.size(); ++i)
        {
            stream << bs.m_data[i];
        }

        return stream;
    }


}