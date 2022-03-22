#include "mcstream.h";
#include "inc.h";
#include <glog/logging.h>

#define read2buf(v) read((char*)&v, sizeof(v))
#define write2buf(v) write((char*)&v, sizeof(v))

namespace minecraft
{
    string mcstream::read_string()
    {
        string s;
        *this >> s;
        return s;
    }
    mcstream& mcstream::operator>>(int8_t& v)
    {
        read2buf(v);
        return *this;
    }
    mcstream& mcstream::operator>>(uint8_t& v)
    {
        read2buf(v);
        return *this;
    }
    mcstream& mcstream::operator>>(int16_t& v)
    {
        read2buf(v);
        return *this;
    }

    mcstream& mcstream::operator>>(uint16_t& v)
    {
        read2buf(v);
        return *this;
    }

    mcstream& mcstream::operator>>(int32_t& v)
    {
        read2buf(v);
        return *this;
    }

    mcstream& mcstream::operator>>(uint32_t& v)
    {
        read2buf(v);
        return *this;
    }

    mcstream& mcstream::operator>>(int64_t& v)
    {
        read2buf(v);
        return *this;
    }

    mcstream& mcstream::operator>>(uint64_t& v)
    {
        read2buf(v);
        return *this;
    }

    mcstream& mcstream::operator>>(bool& v)
    {
        read2buf(v);
        return *this;
    }

    mcstream& mcstream::operator>>(string& s)
    {
        varint len;
        VLOG(VLOG_DEBUG) << "STREAM_POS " << tellg();
        *this >> len;
        VLOG(VLOG_DEBUG) << "STREAM_POS " << tellg();

        safebytebuffer buf;
        buf.reserve(len.val());
        read((char*)buf.data(), len.val());
        VLOG(VLOG_DEBUG) << "STREAM_POS " << tellg();
        s = string((char*)buf.data(), len.val());
        return *this;
    }

    mcstream& mcstream::operator<<(int8_t& v)
    {
        write2buf(v);
        return *this;
    }

    mcstream& mcstream::operator<<(uint8_t& v)
    {
        write2buf(v);
        return *this;
    }

    mcstream& mcstream::operator<<(int16_t& v)
    {
        write2buf(v);
        return *this;
    }

    mcstream& mcstream::operator<<(uint16_t& v)
    {
        write2buf(v);
        return *this;
    }

    mcstream& mcstream::operator<<(int32_t& v)
    {
        write2buf(v);
        return *this;
    }

    mcstream& mcstream::operator<<(uint32_t& v)
    {
        write2buf(v);
        return *this;
    }

    mcstream& mcstream::operator<<(int64_t& v)
    {
        write2buf(v);
        return *this;
    }

    mcstream& mcstream::operator<<(uint64_t& v)
    {
        write2buf(v);
        return *this;
    }

    mcstream& mcstream::operator<<(bool& v)
    {
        write2buf(v);
        return *this;
    }

    mcstream& mcstream::operator<<(string& v)
    {
        varint len(v.length());
        *this << len;
        write(v.c_str(), v.length());
        return *this;
    }
}