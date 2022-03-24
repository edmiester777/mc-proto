#pragma once

// PacketIDs can be equal for different types of packets depending on state. These states are
// meant to label packet IDs for the different states.

namespace minecraft
{
    enum class States
    {
        HANDSHAKING,
        STATUS,
        LOGIN,
        PLAY,
    };

    enum class HandshakingPacketIDs
    {
        O_HANDSHAKE = 0x00
    };

    enum class StatusPacketIds
    {
        O_STATUS = 0x00,
        I_STATUS = 0x00
    };

    enum class LoginPacketIds
    {
        O_LOGIN_START = 0x00,
        O_ENCRYPTION_RESPONSE = 0x01,

        I_DISCONNECT = 0x00,
        I_ENCRYPTION_REQUEST = 0x01,
        I_LOGIN_SUCCESS = 0x02,
    };

    enum class PlayPacketIds
    {
        O_PING = 0x1D,
        O_KEEPALIVE = 0x0F,

        I_SPAWN_ENTITY = 0x00,
        I_SPAWN_EXPERIENCE_ORB = 0x01,
        I_PING = 0x30,
        I_KEEPALIVE = 0x21,
    };
}