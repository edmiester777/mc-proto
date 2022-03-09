#include "nbt.h"

void minecraft::NBTTagBase::write(ostream& stream) const
{
    // we have to write the type byte first
    uint8_t type = this->type();
    stream.write((char*)&type, sizeof(uint8_t));

    // write the rest of our content
    this->write_data(stream);
}
