# CMakeList.txt : CMake project for mc-proto, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

add_library (mc-proto STATIC
    "client.cpp" 
    "packetreader.cpp" 
    "uncompressedpacketreader.cpp")
target_link_libraries(mc-proto
    "sockpp-static"
    glog::glog
)