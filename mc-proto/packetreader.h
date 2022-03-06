#pragma once

#include <memory>
#include <sockpp/tcp_connector.h>

namespace minecraft
{
    using namespace std;
    typedef struct Packet
    {
        bool valid = false;
        shared_ptr<uint8_t> data;
        size_t dataLen;
        int packetId;
    };

    class PacketReader
    {
    public:
        virtual Packet readPacket(sockpp::stream_socket& conn, bool& err) = 0;

        int readVarInt(sockpp::stream_socket& conn, int& size, bool& err);
        void writeVarInt(sockpp::stream_socket& conn, int val, bool& err);
    };
}