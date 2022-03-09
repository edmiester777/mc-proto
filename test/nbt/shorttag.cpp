#include <gtest/gtest.h>
#include <mc-proto/nbt/shorttag.h>

using namespace minecraft;

TEST(NBTShortTag, ConstructFromStream)
{
    stringstream stream;
    const int16_t expectedVal = 0xDF;
    const int16_t networkVal = htons(expectedVal);

    stream.write((char*)&networkVal, sizeof(int16_t));

    NBTShortTag tag(stream);
    EXPECT_EQ(expectedVal, tag.value());
}

TEST(NBTShortTag, WriteToStream)
{
    const uint8_t tagType = NBTTagTypes::TAG_SHORT;
    const int16_t expectedVal = 0xDF;
    const int16_t expectedNetworkVal = htons(expectedVal);
    stringstream stream;
    NBTShortTag tag(expectedVal);

    tag.write(stream);

    uint8_t outTag;
    int16_t networkValue;
    stream.read((char*)&outTag, sizeof(uint8_t));
    stream.read((char*)&networkValue, sizeof(int16_t));

    EXPECT_EQ(tagType, outTag);
    EXPECT_EQ(expectedNetworkVal, networkValue);
}