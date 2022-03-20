# CMakeList.txt : CMake project for mc-proto, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

add_library (mc-proto STATIC
    "varint.cpp"
    "safebytebuffer.cpp"
    "client.cpp" 
    "compressionhelper.cpp"
    "packetreader.cpp"
    "mcstream.cpp"

    "nbt/tag.cpp"
    "nbt/compoundtag.cpp"
    "nbt/bytetag.cpp"
    "nbt/shorttag.cpp"
    "nbt/inttag.cpp"
    "nbt/longtag.cpp"
    "nbt/floattag.cpp"
    "nbt/doubletag.cpp"
    "nbt/stringtag.cpp"
    "nbt/bytearraytag.cpp"
    "nbt/intarraytag.cpp"
    "nbt/longarraytag.cpp"
    "nbt/listtag.cpp"

    "packets/packet.cpp"
    "packets/inbound/status.cpp"
    "packets/outbound/handshake.cpp"
    "packets/outbound/status.cpp"
)
target_link_libraries(mc-proto
    "sockpp-static"
    glog::glog
    zlibstatic
)