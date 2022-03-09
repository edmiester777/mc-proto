#include <gtest/gtest.h>
#include <mc-proto/nbt/bytearraytag.h>

using namespace minecraft;

TEST(NBTByteArrayTag, ReadWriteStream)
{
    vector<uint8_t> bytes;
    for (uint8_t i = 0; i < 100; ++i)
    {
        bytes.push_back(i);
    }
    stringstream stream;

    NBTByteArrayTag tag1(bytes);
    tag1.write_data(stream);
    NBTByteArrayTag tag2(stream);

    EXPECT_EQ(NBTTagTypes::TAG_BYTE_ARRAY, tag1.type());
    EXPECT_EQ(tag1.size(), tag2.size());
    for (int i = 0; i < tag1.size(); ++i)
    {
        EXPECT_EQ(tag1[i], tag2[i]);
    }
}