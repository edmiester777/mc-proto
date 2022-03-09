#pragma once

// PacketIDs can be equal for different types of packets depending on state. These states are
// meant to label packet IDs for the different states.

namespace minecraft
{
    enum States
    {
        HANDSHAKING,
        STATUS,
        LOGIN,
        PLAY,
    };

    enum HandshakingPacketIDs
    {
        S_HANDSHAKE = 0x00
    };
}