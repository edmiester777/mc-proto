# CMakeList.txt : CMake project for mc-proto, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

add_library (mc-proto STATIC
    "client.cpp" 
    "packetreader.cpp" 

    "nbt/compoundtag.cpp"
    "nbt/bytetag.cpp"
    "nbt/shorttag.cpp"
    "nbt/inttag.cpp"
    "nbt/longtag.cpp"
    "nbt/floattag.cpp"
    "nbt/doubletag.cpp"

    "uncompressedpacketreader.cpp"
    "packets/packetobject.cpp"
    "packets/outbound/handshake.cpp")
target_link_libraries(mc-proto
    "sockpp-static"
    glog::glog
    zlibstatic
)