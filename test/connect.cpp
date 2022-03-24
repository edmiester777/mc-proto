#include <glog/logging.h>
#include <mc-proto/client.h>

using namespace minecraft;

class Listener : public ClientEventListener
{
public:

    // Inherited via ClientEventListener
    virtual void OnLoginSuccess(Client& c, InboundLoginPacket& packet) override
    {
        LOG(INFO) << "Logged in as " << packet.username();
    }

    virtual void OnLoginFailed(Client& c) override
    {
        LOG(WARNING) << "Login attempt failed.";
    }

    // Inherited via ClientEventListener
    virtual void OnSpawnEntity(Client& c, InboundSpawnEntityPacket& packet) override
    {
    }

    // Inherited via ClientEventListener
    virtual void OnSpawnExperienceOrb(Client& c, InboundSpawnExperienceOrbPacket& packet) override
    {
    }

    // Inherited via ClientEventListener
    virtual void OnSpawnLivingEntity(Client& c, InboundSpawnLivingEntityPacket& packet) override
    {
    }

    // Inherited via ClientEventListener
    virtual void OnSpawnPainting(Client& c, InboundSpawnPaintingPacket& packet) override
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