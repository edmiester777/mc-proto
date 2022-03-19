#include <glog/logging.h>
#include <mc-proto/client.h>

using namespace minecraft;

int main(int argc, char** argv)
{
    FLAGS_v = 10;
    FLAGS_logtostdout = true;
    FLAGS_logbuflevel = google::GLOG_INFO;
    google::InitGoogleLogging(argv[0]);

    LOG(INFO) << "TEST";

    Client c("localhost", 25565);
    if (!c.connect())
        return -1;

    c.run();
}