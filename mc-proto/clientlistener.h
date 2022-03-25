#pragma once

#include "packets/inbound/login.h"
#include "packets/inbound/play/spawnentity.h"
#include "packets/inbound/play/spawnexperienceorb.h"
#include "packets/inbound/play/spawnlivingentity.h"
#include "packets/inbound/play/spawnpainting.h"
#include "packets/inbound/play/spawnplayer.h"
#include "packets/inbound/play/entityanimation.h"
#include "packets/inbound/play/ackdig.h"
#include "packets/inbound/play/blockbreakanim.h"
#include "packets/inbound/play/blockentitydata.h"

namespace minecraft
{
    class Client;

    class ClientEventListener
    {
    public:
        virtual void OnLoginSuccess(Client& c, const InboundLoginPacket& packet) = 0;
        virtual void OnLoginFailed(Client& c) = 0;
        virtual void OnSpawnEntity(Client& c, const InboundSpawnEntityPacket& packet) = 0;
        virtual void OnSpawnExperienceOrb(Client& c, const InboundSpawnExperienceOrbPacket& packet) = 0;
        virtual void OnSpawnLivingEntity(Client& c, const InboundSpawnLivingEntityPacket& packet) = 0;
        virtual void OnSpawnPainting(Client& c, const InboundSpawnPaintingPacket& packet) = 0;
        virtual void OnSpawnPlayer(Client& c, const InboundSpawnPlayerPacket& packet) = 0;
        virtual void OnPlayerAnimation(Client& c, const InboundEntityAnimationPacket& packet) = 0;
        virtual void OnBlockDigAcknowleged(Client& c, const InboundAckDigPacket& packet) = 0;
        virtual void OnBlockBreakAnimation(Client& c, const InboundBlockBreakAnimationPacket& packet) = 0;
        virtual void OnBlockData(Client& c, const InboundBlockEntityDataPacket& packet) = 0;
    };
}