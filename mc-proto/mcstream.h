#pragma once

#include <sstream>

namespace minecraft
{
    using namespace std;

    class mcstream : public stringstream
    {
    public:
        mcstream() : stringstream() { }

        string read_string();
    };
}