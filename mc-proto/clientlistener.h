#pragma once

#include "packets/inbound/login.h"
#include "packets/inbound/play/spawnentity.h"
#include "packets/inbound/play/spawnexperienceorb.h"
#include "packets/inbound/play/spawnlivingentity.h"

namespace minecraft
{
    class Client;

    class ClientEventListener
    {
    public:
        virtual void OnLoginSuccess(Client& c, InboundLoginPacket& packet) = 0;
        virtual void OnLoginFailed(Client& c) = 0;
        virtual void OnSpawnEntity(Client& c, InboundSpawnEntityPacket& packet) = 0;
        virtual void OnSpawnExperienceOrb(Client& c, InboundSpawnExperienceOrbPacket& packet) = 0;
        virtual void OnSpawnLivingEntity(Client& c, InboundSpawnLivingEntityPacket& packet) = 0;
    };
}