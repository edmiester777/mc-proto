#pragma once

#include <memory>
#include <sockpp/tcp_connector.h>
#include <mc-proto/nbt/nbt.h>

namespace minecraft
{
    class PacketReader
    {
    public:

        int readVarInt(sockpp::stream_socket& conn, int& size, bool& err);
        void writeVarInt(sockpp::stream_socket& conn, int val, bool& err);
    };
}