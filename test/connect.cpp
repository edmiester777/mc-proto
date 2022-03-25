#include <glog/logging.h>
#include <mc-proto/client.h>

using namespace minecraft;

class Listener : public ClientEventListener
{
public:

    virtual void OnLoginSuccess(Client& c, const InboundLoginPacket& packet) override
    {
    }
    virtual void OnLoginFailed(Client& c) override
    {
    }
    virtual void OnSpawnEntity(Client& c, const InboundSpawnEntityPacket& packet) override
    {
    }
    virtual void OnSpawnExperienceOrb(Client& c, const InboundSpawnExperienceOrbPacket& packet) override
    {
    }
    virtual void OnSpawnLivingEntity(Client& c, const InboundSpawnLivingEntityPacket& packet) override
    {
    }
    virtual void OnSpawnPainting(Client& c, const InboundSpawnPaintingPacket& packet) override
    {
    }
    virtual void OnSpawnPlayer(Client& c, const InboundSpawnPlayerPacket& packet) override
    {
    }
    virtual void OnPlayerAnimation(Client& c, const InboundEntityAnimationPacket& packet) override
    {
    }
    virtual void OnBlockDigAcknowleged(Client& c, const InboundAckDigPacket& packet) override
    {
    }
    virtual void OnBlockBreakAnimation(Client& c, const InboundBlockBreakAnimationPacket& packet) override
    {
    }
    virtual void OnBlockData(Client& c, const InboundBlockEntityDataPacket& packet) override
    {
    }
};

int main(int argc, char** argv)
{
    google::InitGoogleLogging(argv[0]);
    FLAGS_v = VLOG_INFO;
    FLAGS_logtostdout = true;
    FLAGS_logbuflevel = google::GLOG_INFO;

    LOG(INFO) << "TEST";

    Client c("localhost", 25565, shared_ptr<ClientEventListener>(new Listener()));
    if (!c.connect())
        return -1;

    c.login("edmiester777");

    c.run();
}