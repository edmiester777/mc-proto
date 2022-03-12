#include "safebytebuffer.h"
#include "inc.h"
#include <streambuf>
#include <istream>
#include <sstream>
#include <glog/logging.h>

#define CAST_WRITE_STACK(v) push_buffer((uint8_t*)&v, sizeof(v))

using namespace minecraft;
using namespace std;

std::ostream& minecraft::safebytebuffer::operator<<(std::ostream& stream) const
{
    stream.write((char*)&(*this)[0], size());
    return stream;
}

void minecraft::safebytebuffer::push_buffer(std::uint8_t* buf, size_t len)
{
    // this strategy is in leau of the vector::insert method because we don't want to force
    // frequent re-allocations for expansion.

    // check if we need to resize buffer
    if (size() + len > capacity())
    {
        // we will resize buffer to max(capacity * 2, sizeibuf * 2) to limit
        // future memory allocation/copy time.
        int newsize = max(capacity() * 2, len * 2);
        reserve(newsize);
    }

    // copying input buffer to next block location
    memcpy(data(), buf, len);
}

void minecraft::safebytebuffer::push_stream(std::istream& stream)
{
    // getting number of bytes left to read in stream
    int start = stream.peek();
    stream.seekg(stream.end);
    int end = stream.peek();
    stream.seekg(start);
    int length = end - start;

    // allocating buffer
    uint8_t* buf = new uint8_t[length];

    // pushing to our buffer
    push_buffer(buf, length);

    // cleaning up
    delete[] buf;
}

void minecraft::safebytebuffer::write(bool b)
{
    write((uint8_t)b);
}

void minecraft::safebytebuffer::write(uint8_t byte)
{
    CAST_WRITE_STACK(byte);
}

void minecraft::safebytebuffer::write(int16_t s)
{
    int16_t networkval = htons(s);
    CAST_WRITE_STACK(networkval);
}

void minecraft::safebytebuffer::write(uint16_t s)
{
    write((int16_t)s);
}

void minecraft::safebytebuffer::write(int32_t i)
{
    int32_t networkval = htonl(i);
    CAST_WRITE_STACK(networkval);
}

void minecraft::safebytebuffer::write(uint32_t i)
{
    write((int32_t)i);
}

void minecraft::safebytebuffer::write(int64_t l)
{
    int64_t networkval = htonll(l);
    CAST_WRITE_STACK(networkval);
}

void minecraft::safebytebuffer::write(uint64_t l)
{
    write((int64_t)l);
}

void minecraft::safebytebuffer::write(float f)
{
    float networkval = htonf(f);
    CAST_WRITE_STACK(networkval);
}

void minecraft::safebytebuffer::write(double d)
{
    double networkval = htond(d);
    CAST_WRITE_STACK(networkval);
}

void minecraft::safebytebuffer::write(string s)
{
    push_buffer((uint8_t*)s.c_str(), s.length() + 1);
}

void minecraft::safebytebuffer::writeVarInt(int i)
{
    int nbytes = 0;
    unsigned int value = htonl(i);

    while (true) 
    {
        uint8_t lval = value;
        if ((value & ~0x7F) == 0)
        {
            CAST_WRITE_STACK(lval);
            return;
        }

        lval = (value & 0x7F) | 0x80;
        CAST_WRITE_STACK(lval);
        // Note: >>> means that the sign bit is shifted with the rest of the number rather than being left alone
        value >>= 7;
    }

    VLOG(VLOG_INFO)
        << "Wrote VarInt in " << nbytes << " byte(s).";
}
