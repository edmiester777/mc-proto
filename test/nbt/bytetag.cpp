#include <gtest/gtest.h>
#include <mc-proto/nbt/nbt.h>
#include <mc-proto/nbt/bytetag.h>

using namespace minecraft;

TEST(NBTByteTag, ConstructFromStream)
{
    const uint8_t byteVal = 0xF4;
    mcstream stream;
    stream << byteVal;

    NBTByteTag tag(stream);

    EXPECT_EQ(byteVal, tag.value());
}

TEST(NBTByteTag, WriteToStream)
{
    const uint8_t byteVal = 0xF4;
    const uint8_t expectedBytes[2] = {
        NBTTagTypes::TAG_BYTE,
        byteVal
    };
    NBTByteTag tag(byteVal);

    mcstream stream;
    tag.write(stream);

    uint8_t readBytes[2];
    stream.read((char*)readBytes, 2);

    EXPECT_TRUE(memcmp(expectedBytes, readBytes, 2) == 0);
}