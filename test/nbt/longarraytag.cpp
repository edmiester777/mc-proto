#include <gtest/gtest.h>
#include <mc-proto/nbt/longarraytag.h>

using namespace minecraft;

TEST(NBTLongArrayTag, ReadWriteStream)
{
    stringstream stream;
    vector<int64_t> values;
    for (int i = 0; i < 100; ++i)
    {
        values.push_back(i - 100l);
    }
    NBTLongArrayTag tag1(values);
    tag1.write_data(stream);
    NBTLongArrayTag tag2(stream);

    EXPECT_EQ(NBTTagTypes::TAG_LONG_ARRAY, tag1.type());
    EXPECT_EQ(tag1.size(), tag2.size());
    for (int i = 0; i < tag1.size(); ++i)
    {
        EXPECT_EQ(tag1[i], tag2[i]);
    }
}