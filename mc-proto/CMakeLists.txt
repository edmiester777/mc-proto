# CMakeList.txt : CMake project for mc-proto, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

add_library (mc-proto STATIC
    "varint.cpp"
    "position.cpp"
    "safebytebuffer.cpp"
    "client.cpp" 
    "compressionhelper.cpp"
    "packetreader.cpp"
    "mcstream.cpp"
    "uuid.cpp"

    "minecraft/entitytypes.cpp"

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
    "packets/inbound/login.cpp"
    "packets/inbound/play/keepalive.cpp"
    "packets/inbound/play/ping.cpp"
    "packets/inbound/play/spawnentity.cpp"
    "packets/inbound/play/spawnexperienceorb.cpp"
    "packets/inbound/play/spawnlivingentity.cpp"
    "packets/inbound/play/spawnpainting.cpp"
    "packets/inbound/play/spawnplayer.cpp"
    "packets/inbound/play/entityanimation.cpp"
    "packets/outbound/handshake.cpp"
    "packets/outbound/status.cpp"
    "packets/outbound/login.cpp"
)
target_link_libraries(mc-proto
    "sockpp-static"
    glog::glog
    zlibstatic
)