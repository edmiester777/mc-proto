#include <gtest/gtest.h>
#include <mc-proto/nbt/intarraytag.h>

using namespace minecraft;

TEST(NBTIntArrayTag, ReadWriteStream)
{
    stringstream stream;
    vector<int32_t> vals;
    for (int i = 0; i < 100; ++i)
    {
        vals.push_back(i - 50);
    }

    NBTIntArrayTag tag1(vals);
    tag1.write(stream);
    uint8_t tagType;
    stream.read((char*)&tagType, sizeof(uint8_t));
    EXPECT_EQ(NBTTagTypes::TAG_INT_ARRAY, tagType);

    NBTIntArrayTag tag2(stream);

    EXPECT_EQ(tag1.size(), tag2.size());
    for (int i = 0; i < tag1.size(); ++i)
    {
        EXPECT_EQ(tag1[i], tag2[i]);
    }
}