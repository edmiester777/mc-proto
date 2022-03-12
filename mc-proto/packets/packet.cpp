#include "packet.h"
#include <glog/logging.h>

using namespace std;
using namespace minecraft;

safebytebuffer minecraft::Packet::serialize() const
{
    // we take care of writing the packetid, but the rest should be handled
    // in child implementations of ::serialize_data
    safebytebuffer buf;
    buf.writeVarInt(id());

    serialize_data(buf);
    return buf;
}

void minecraft::Packet::serialize_data(safebytebuffer& buf) const
{
    throw E_NOTIMPL;
}
