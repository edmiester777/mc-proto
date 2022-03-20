#include "status.h"

namespace minecraft
{
    InboundStatusPacket::InboundStatusPacket(mcstream& input)
    {
        m_responseStr = input.read_string();
    }

    string InboundStatusPacket::to_string() const
    {
        stringstream stream;
        stream << "RESPONSE_JSON(" << m_responseStr << ")";
        return stream.str();
    }
}