#include <gtest/gtest.h>
#include <mc-proto/nbt/inttag.h>

using namespace minecraft;

TEST(NBTIntTag, ConstructFromStream)
{
    const int32_t expectedValue = 0x43F3DE;
    const int32_t networkvalue = htonl(expectedValue);

    stringstream stream;
    stream.write((char*)&networkvalue, sizeof(int32_t));

    NBTIntTag tag(stream);
    EXPECT_EQ(expectedValue, tag.value());
}

TEST(NBTIntTag, WriteToStream)
{
    const int32_t expectedValue = 0x43F3DE;
    const int32_t expectedNetworkValue = htonl(expectedValue);
    NBTIntTag tag(expectedValue);
    stringstream stream;
    tag.write(stream);

    uint8_t tagType;
    int32_t value;
    stream.read((char*)&tagType, sizeof(uint8_t));
    stream.read((char*)&value, sizeof(int32_t));

    EXPECT_EQ(NBTTagTypes::TAG_INT, tagType);
    EXPECT_EQ(expectedNetworkValue, value);
}