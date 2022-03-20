#include "safebytebuffer.h"
#include "inc.h"
#include "varint.h"
#include <streambuf>
#include <istream>
#include <sstream>
#include <glog/logging.h>

#define CAST_WRITE_STACK(v) push_buffer((uint8_t*)&v, sizeof(v))

using namespace minecraft;
using namespace std;

std::ostream& minecraft::operator<<(std::ostream& stream, const safebytebuffer& buf)
{
    stream.write((char*)buf.data(), buf.size());
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
    copy(buf, buf + len, back_inserter(*this));
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

void minecraft::safebytebuffer::push(bool b)
{
    push((uint8_t)b);
}

void minecraft::safebytebuffer::push(uint8_t byte)
{
    CAST_WRITE_STACK(byte);
}

void minecraft::safebytebuffer::push(int16_t s)
{
    int16_t networkval = htons(s);
    CAST_WRITE_STACK(networkval);
}

void minecraft::safebytebuffer::push(uint16_t s)
{
    push((int16_t)s);
}

void minecraft::safebytebuffer::push(int32_t i)
{
    int32_t networkval = htonl(i);
    CAST_WRITE_STACK(networkval);
}

void minecraft::safebytebuffer::push(uint32_t i)
{
    push((int32_t)i);
}

void minecraft::safebytebuffer::push(int64_t l)
{
    int64_t networkval = htonll(l);
    CAST_WRITE_STACK(networkval);
}

void minecraft::safebytebuffer::push(uint64_t l)
{
    push((int64_t)l);
}

void minecraft::safebytebuffer::push(float f)
{
    float networkval = htonf(f);
    CAST_WRITE_STACK(networkval);
}

void minecraft::safebytebuffer::push(double d)
{
    double networkval = htond(d);
    CAST_WRITE_STACK(networkval);
}

void minecraft::safebytebuffer::push(string s)
{
    push(varint(s.length()));
    push_buffer((uint8_t*)s.c_str(), s.length());
}

void minecraft::safebytebuffer::push(varint i)
{
    i.write([this](uint8_t b) {
        push_buffer((uint8_t*)&b, 1);
    });
}
