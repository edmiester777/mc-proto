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
        uint16_t network;
        read2buf(network);
        v = ntohs(network);
        return *this;
    }

    mcstream& mcstream::operator>>(uint16_t& v)
    {
        uint16_t network;
        read2buf(network);
        v = ntohs(network);
        return *this;
    }

    mcstream& mcstream::operator>>(int32_t& v)
    {
        uint32_t network;
        read2buf(network);
        v = ntohl(network);
        return *this;
    }

    mcstream& mcstream::operator>>(uint32_t& v)
    {
        uint32_t network;
        read2buf(network);
        v = ntohl(network);
        return *this;
    }

    mcstream& mcstream::operator>>(int64_t& v)
    {
        uint64_t network;
        read2buf(network);
        v = ntohll(network);
        return *this;
    }

    mcstream& mcstream::operator>>(uint64_t& v)
    {
        uint64_t network;
        read2buf(network);
        v = ntohll(network);
        return *this;
    }

    mcstream& mcstream::operator>>(double& d)
    {
        uint64_t network;
        read2buf(network);
        d = ntohd(network);
        return *this;
    }

    mcstream& mcstream::operator>>(float& f)
    {
        uint32_t network;
        read2buf(network);
        f = ntohf(network);
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
        *this >> len;

        safebytebuffer buf;
        buf.reserve(len.val());
        read((char*)buf.data(), len.val());
        s = string((char*)buf.data(), len.val());
        return *this;
    }

    mcstream& mcstream::operator<<(const int8_t& v)
    {
        write2buf(v);
        return *this;
    }

    mcstream& mcstream::operator<<(const uint8_t& v)
    {
        write2buf(v);
        return *this;
    }

    mcstream& mcstream::operator<<(const int16_t& v)
    {
        uint16_t network = htons(v);
        write2buf(network);
        return *this;
    }

    mcstream& mcstream::operator<<(const uint16_t& v)
    {
        uint16_t network = htons(v);
        write2buf(network);
        return *this;
    }

    mcstream& mcstream::operator<<(const int32_t& v)
    {
        uint32_t network = htonl(v);
        write2buf(network);
        return *this;
    }

    mcstream& mcstream::operator<<(const uint32_t& v)
    {
        uint32_t network = htonl(v);
        write2buf(network);
        return *this;
    }

    mcstream& mcstream::operator<<(const int64_t& v)
    {
        uint64_t network = htonll(v);
        write2buf(network);
        return *this;
    }

    mcstream& mcstream::operator<<(const uint64_t& v)
    {
        uint64_t network = htonll(v);
        write2buf(network);
        return *this;
    }

    mcstream& mcstream::operator<<(const double& d)
    {
        uint64_t network = htond(d);
        write2buf(network);
        return *this;
    }

    mcstream& mcstream::operator<<(const float& f)
    {
        uint32_t network = htonf(f);
        write2buf(network);
        return *this;
    }

    mcstream& mcstream::operator<<(const bool& v)
    {
        write2buf(v);
        return *this;
    }

    mcstream& mcstream::operator<<(const string& v)
    {
        varint len(v.length());
        *this << len;
        write(v.c_str(), v.length());
        return *this;
    }
}