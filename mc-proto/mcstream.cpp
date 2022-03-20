#include "mcstream.h";
#include "inc.h";

namespace minecraft
{
    string mcstream::read_string()
    {
        varint stringLength;
        (*this) >> stringLength;
        char* strbuf = new char[stringLength.val()];
        read(strbuf, stringLength.val());
        string str(strbuf, stringLength.val());
        delete[] strbuf;
        return str;
    }
}