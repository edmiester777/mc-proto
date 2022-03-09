#include <gtest/gtest.h>
#include <mc-proto/nbt/doubletag.h>

using namespace minecraft;

TEST(NBTDoubleTag, ConstructFromStream)
{
    const double expectedValue = -3285.3583248245;
    const uint64_t networkValue = htond(expectedValue);
    stringstream stream;
    stream.write((char*)&networkValue, sizeof(uint64_t));

    const NBTDoubleTag tag(stream);
    EXPECT_EQ(expectedValue, tag.value());
}

TEST(NBTDoubleTag, WriteToStream)
{
    const double expectedValue = -3285.3583248245;
    const uint64_t expectedNetworkValue = htond(expectedValue);
    const NBTDoubleTag tag(expectedValue);
    stringstream stream;
    
    tag.write(stream);
    uint8_t tagType;
    uint64_t value;
    stream.read((char*)&tagType, sizeof(uint8_t));
    stream.read((char*)&value, sizeof(uint64_t));

    EXPECT_EQ(NBTTagTypes::TAG_DOUBLE, tagType);
    EXPECT_EQ(expectedNetworkValue, value);
}