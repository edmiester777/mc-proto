#include "uncompressedpacketreader.h"
#include <glog/logging.h>

/**
 * https://wiki.vg/Protocol#Packet_format
 */
minecraft::Packet minecraft::UncompressedPacketReader::readPacket(sockpp::stream_socket& conn, bool& err)
{
    int intSize;
    
    int packetLen = readVarInt(conn, intSize, err);
    if (err) return Packet();

    int packetId = readVarInt(conn, intSize, err);
    if (err) return Packet();

    packetLen -= intSize;

    Packet packet;
    packet.dataLen = packetLen;
    packet.packetId = packetId;
    packet.data = shared_ptr<uint8_t>(new uint8_t[packetLen]);

    int readLen = conn.read_n(packet.data.get(), packetLen);

    if (readLen == packetLen)
    {
        DLOG(INFO)
            << "Read packet (" << packetId << ") "
            << "with length " << packetLen;
    }
    else
    {
        LOG(WARNING)
            << "Failed to read packet (" << packetId << ") "
            << conn.last_error_str();
        err = true;
    }

    return packet;
}
