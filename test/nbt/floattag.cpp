#include <gtest/gtest.h>
#include <mc-proto/nbt/floattag.h>

using namespace minecraft;

TEST(NBTFloatTag, ConstructFromStream)
{
    const float expectedValue = 53.55485f;
    const uint32_t networkValue = htonf(expectedValue);
    stringstream stream;
    stream.write((char*)&networkValue, sizeof(uint32_t));

    const NBTFloatTag tag(stream);
    EXPECT_EQ(expectedValue, tag.value());
}

TEST(NBTFloatTag, WriteToStream)
{
    const float expectedValue = 53.55485f;
    const uint32_t expectedNetworkValue = htonf(expectedValue);
    const NBTFloatTag tag(expectedValue);

    stringstream stream;
    tag.write(stream);
    uint8_t tagType;
    uint32_t value;
    stream.read((char*)&tagType, sizeof(uint8_t));
    stream.read((char*)&value, sizeof(uint32_t));

    EXPECT_EQ(NBTTagTypes::TAG_FLOAT, tagType);
    EXPECT_EQ(expectedNetworkValue, value);
}