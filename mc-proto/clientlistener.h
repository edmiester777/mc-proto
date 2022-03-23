#pragma once

#include "packets/inbound/login.h"
#include "packets/inbound/play/spawnentity.h"

namespace minecraft
{
    class Client;

    class ClientEventListener
    {
    public:
        virtual void OnLoginSuccess(Client& c, InboundLoginPacket& packet) = 0;
        virtual void OnLoginFailed(Client& c) = 0;
        virtual void OnSpawnEntity(Client& c, InboundSpawnEntityPacket& packet) = 0;
    };
}