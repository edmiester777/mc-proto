#include "packet.h"

using namespace std;
using namespace minecraft;

int minecraft::Packet::id() const
{
    return m_id;
}

safebytebuffer minecraft::Packet::serializeData(size_t& bufferSize)
{
    if (!m_data)
        return safebytebuffer();

    stringstream stream;
    m_data->write(stream);
    
    // getting size of payload
    stream.seekg(stream.end);
    int length = stream.peek();
    stream.seekg(stream.beg);

    safebytebuffer buf(new uint8_t[length]);
    stream.read((char*)buf.get(), length);
    return buf;
}

safebytebuffer minecraft::Packet::serializeDataCompressed(size_t& bufferSize)
{
    return safebytebuffer();
}
