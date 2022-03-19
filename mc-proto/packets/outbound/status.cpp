#include "status.h"

using namespace std;
using namespace minecraft;

minecraft::OutboundStatusPacket::OutboundStatusPacket()
{
}

minecraft::OutboundStatusPacket::OutboundStatusPacket(safebytebuffer& buffer)
{
}

void minecraft::OutboundStatusPacket::serialize_data(safebytebuffer& buffer) const
{
    // no data is sent as a part of this payload.
}

string minecraft::OutboundStatusPacket::to_string() const
{
    return "empty payload";
}
