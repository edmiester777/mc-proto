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

safebytebuffer& minecraft::safebytebuffer::operator<<(const bool b)
{
    push(b);
    return *this;
}

safebytebuffer& minecraft::safebytebuffer::operator<<(const uint8_t byte)
{
    push(byte);
    return *this;
}

safebytebuffer& minecraft::safebytebuffer::operator<<(const int16_t s)
{
    push(s);
    return *this;
}

safebytebuffer& minecraft::safebytebuffer::operator<<(const uint16_t s)
{
    push(s);
    return *this;
}

safebytebuffer& minecraft::safebytebuffer::operator<<(const int32_t i)
{
    push(i);
    return *this;
}

safebytebuffer& minecraft::safebytebuffer::operator<<(const uint32_t i)
{
    push(i);
    return *this;
}

safebytebuffer& minecraft::safebytebuffer::operator<<(const int64_t l)
{
    push(l);
    return *this;
}

safebytebuffer& minecraft::safebytebuffer::operator<<(const uint64_t l)
{
    push(l);
    return *this;
}

safebytebuffer& minecraft::safebytebuffer::operator<<(const float f)
{
    push(f);
    return *this;
}

safebytebuffer& minecraft::safebytebuffer::operator<<(const double d)
{
    push(d);
    return *this;
}

safebytebuffer& minecraft::safebytebuffer::operator<<(const string& s)
{
    push(s);
    return *this;
}

safebytebuffer& minecraft::safebytebuffer::operator<<(const varint& i)
{
    push(i);
    return *this;
}

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
    uint16_t networkval = htons(s);
    CAST_WRITE_STACK(networkval);
}

void minecraft::safebytebuffer::push(int32_t i)
{
    uint32_t networkval = htonl(i);
    CAST_WRITE_STACK(networkval);
}

void minecraft::safebytebuffer::push(uint32_t i)
{
    uint32_t networkval = htonl(i);
    CAST_WRITE_STACK(networkval);
}

void minecraft::safebytebuffer::push(int64_t l)
{
    uint64_t networkval = htonll(l);
    CAST_WRITE_STACK(networkval);
}

void minecraft::safebytebuffer::push(uint64_t l)
{
    uint64_t networkval = htonll(l);
    CAST_WRITE_STACK(networkval);
}

void minecraft::safebytebuffer::push(float f)
{
    uint32_t networkval = htonf(f);
    CAST_WRITE_STACK(networkval);
}

void minecraft::safebytebuffer::push(double d)
{
    uint64_t networkval = htond(d);
    CAST_WRITE_STACK(networkval);
}

void minecraft::safebytebuffer::push(const string& s)
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
