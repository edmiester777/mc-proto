#include "handshake.h"

minecraft::OutboundHandshakePacket::OutboundHandshakePacket(string serverAddr, uint16_t port, States nextState)
{
    if (nextState != States::LOGIN && nextState != States::STATUS)
        throw E_INVALIDARG;

    m_serverAddr = serverAddr;
    m_port = port;
    m_nextState = nextState;
}

void minecraft::OutboundHandshakePacket::serialize_data(safebytebuffer& buf) const
{
    buf.push(varint(MC_PROTOCOL_VERSION));
    buf.push(m_serverAddr);
    buf.push(m_port);
    buf.push(varint((int)m_nextState));
}

std::string minecraft::OutboundHandshakePacket::to_string() const
{
    return "empty payload";
}
