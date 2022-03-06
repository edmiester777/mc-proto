#include "packetreader.h"
#include "inc.h"
#include <glog/logging.h>

/**
 * https://wiki.vg/Protocol#VarInt_and_VarLong
 */
int minecraft::PacketReader::readVarInt(sockpp::stream_socket& conn, int& size, bool& err)
{
    size = 0;
    err = false;

    uint8_t byte;
    int val = 0;

    while (true)
    {
        VLOG(VLOG_DEBUG) << "Attempting to read VarInt byte...";
        size_t rec = conn.read_n(&byte, 1);
        if (rec == -1)
        {
            VLOG(VLOG_ERROR)
                << "Error encountered while reading data from socket: "
                << conn.last_error_str();
            err = true;
            break;
        }

        val |= (byte & 0x7F) << (size * 7);
        size += 1;

        if (size > 5)
        {
            err = true;
            LOG(WARNING) << "VarInt length too long. Aborting.";
            break;
        }

        // break loop if this byte signals no more data
        if ((byte & 0x80) != 0x80) {
            break;
        }
    }

    int result = ntohl(val);
    VLOG(VLOG_INFO)
        << "Read VarInt in " << size << " bytes "
        << "with value " << result;

    return result;
}

/**
 * https://wiki.vg/Protocol#VarInt_and_VarLong
 */
void minecraft::PacketReader::writeVarInt(sockpp::stream_socket& conn, int val, bool& err)
{
    int nbytes = 0;
    err = false;
    int value = htonl(val);

    while (true)
    {
        VLOG(VLOG_DEBUG) << "Attempting to send VarInt byte...";

        int sentLen;
        uint8_t nval = value;
        if ((value & ~0x7F) == 0) 
        {
            sentLen = conn.write_n(&nval, 1);
            if (nval == -1)
                err = true;
            return;
        }

        nval |= 0x80;
        sentLen = conn.write_n(&nval, 1);
        if (sentLen != 1)
        {
            err = true;
            return;
        }
        value >>= 7;
        ++nbytes;
    }

    VLOG(VLOG_INFO)
        << "Sent VarInt in " << nbytes << " bytes "
        "with value " << val;
}
