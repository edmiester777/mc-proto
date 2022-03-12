#include "handshake.h"

minecraft::OutboundHandshakePacket::OutboundHandshakePacket(safebytebuffer buf)
{
}

minecraft::OutboundHandshakePacket::OutboundHandshakePacket(string serverAddr, uint16_t port, States nextState)
{
    if (nextState != States::LOGIN && nextState != States::STATUS)
        throw E_INVALIDARG;

    m_serverAddr = serverAddr;
    m_port = port;
    m_nextState = nextState;
}

int minecraft::OutboundHandshakePacket::id() const
{
    return (int)HandshakingPacketIDs::O_HANDSHAKE;
}


void minecraft::OutboundHandshakePacket::serialize_data(safebytebuffer& buf) const
{
    buf.writeVarInt(MC_PROTOCOL_VERSION);
    buf.write(m_serverAddr);
    buf.write(m_port);
    buf.writeVarInt((int)m_nextState);
}
