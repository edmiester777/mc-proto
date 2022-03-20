#include "packet.h"
#include <iomanip>
#include <glog/logging.h>

using namespace std;
using namespace minecraft;

std::ostream& minecraft::operator<<(std::ostream& stream, const Packet& packet)
{
    return stream
        << "STATUS(" << packet.status_name() << ") "
        << "CLASS(" << packet.class_name() << ") "
        << "PACKET_ID(0x" << setfill('0') << setw(2) << hex << packet.id() << ") "
        << "CONTENT: " << packet.to_string();
}

safebytebuffer minecraft::Packet::serialize() const
{
    // we take care of writing the packetid, but the rest should be handled
    // in child implementations of ::serialize_data
    safebytebuffer buf;
    buf.push(varint(id()));

    serialize_data(buf);
    return buf;
}

string minecraft::Packet::to_string() const
{
    return "<UNIMPLEMENTED to_string()>";
}

void minecraft::Packet::serialize_data(safebytebuffer& buf) const
{
    throw E_NOTIMPL;
}
