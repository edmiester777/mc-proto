#pragma once
#include "packetreader.h"

namespace minecraft
{
    class UncompressedPacketReader : public PacketReader
    {
    public:
        // Inherited via PacketReader
        virtual Packet readPacket(sockpp::stream_socket& conn, bool& err) override;
    };
}