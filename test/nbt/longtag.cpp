#include <gtest/gtest.h>
#include <mc-proto/nbt/longtag.h>

using namespace minecraft;

TEST(NBTLongTag, ConstructFromStream)
{
    int64_t expectedValue = 0x6512F5DE9F4D520F;
    int64_t networkValue = htonll(expectedValue);
    stringstream stream;
    stream.write((char*)&networkValue, sizeof(int64_t));

    NBTLongTag tag(stream);
    EXPECT_EQ(expectedValue, tag.value());
}

TEST(NBTLongTag, WriteToStream)
{
    const int64_t expectedValue = 0x6512F5DE9F4D520F;
    const int64_t expectedNetworkValue = htonll(expectedValue);
    uint8_t tagType;
    int64_t value;

    stringstream stream;
    NBTLongTag tag(expectedValue);
    tag.write(stream);

    stream.read((char*)&tagType, sizeof(uint8_t));
    stream.read((char*)&value, sizeof(int64_t));

    EXPECT_EQ(NBTTagTypes::TAG_LONG, tagType);
    EXPECT_EQ(expectedNetworkValue, value);
}