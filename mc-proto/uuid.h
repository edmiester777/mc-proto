#pragma once

#include "inc.h"

namespace minecraft
{
    class uuid
    {
    public:
        uuid();
        uuid(uint64_t ms, uint64_t ls);
        uuid(string& s);

        string to_string() const;

        friend mcstream& operator>>(mcstream& stream, uuid& u);
        friend mcstream& operator<<(mcstream& stream, uuid& u);
        friend std::ostream& operator<<(ostream& stream, uuid& u);

    private:
        uint64_t m_mostSignificant;
        uint64_t m_leastSignificant;
    };
}