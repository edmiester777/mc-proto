#include <glog/logging.h>
#include <mc-proto/client.h>

using namespace minecraft;

class Listener : public ClientEventListener
{
public:

    // Inherited via ClientEventListener
    virtual void OnLoginSuccess(Client& c, InboundLoginPacket& packet) override
    {
        LOG(INFO) << packet;
        exit(0);
    }

    virtual void OnLoginFailed(Client& c) override
    {

    }
};

int main(int argc, char** argv)
{
    FLAGS_v = 10;
    FLAGS_logtostdout = true;
    FLAGS_logbuflevel = google::GLOG_INFO;
    google::InitGoogleLogging(argv[0]);

    LOG(INFO) << "TEST";

    Client c("localhost", 25565, shared_ptr<ClientEventListener>(new Listener()));
    if (!c.connect())
        return -1;

    c.login("edmiester777");

    c.run();
}