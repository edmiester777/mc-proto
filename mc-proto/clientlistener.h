#pragma once

#include "packets/inbound/login.h"

namespace minecraft
{
    class Client;

    class ClientEventListener
    {
    public:
        virtual void OnLoginSuccess(Client& c, InboundLoginPacket& packet) = 0;
        virtual void OnLoginFailed(Client& c) = 0;
    };
}