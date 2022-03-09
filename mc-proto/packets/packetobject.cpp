#include "packetobject.h"

using namespace std;

minecraft::PacketObject::PacketObject(istream datastream)
{
    nbt::NBT data(datastream);
    from_nbt(data);
}
