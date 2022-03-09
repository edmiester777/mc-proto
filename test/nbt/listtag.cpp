#include <gtest/gtest.h>
#include <mc-proto/nbt/listtag.h>
#include <mc-proto/nbt/longtag.h>

using namespace minecraft;

TEST(NBTListTag, ReadWriteStream)
{
    vector<shared_ptr<NBTTagBase>> expectedValues;
    for (int i = 0; i < 100; ++i)
    {
        expectedValues.push_back(make_shared<NBTLongTag>(NBTLongTag(i)));
    }

    NBTListTag tag1(TAG_LONG, expectedValues);
    stringstream stream;
    tag1.write_data(stream);
    NBTListTag tag2(stream);

    EXPECT_EQ(tag1.type(), TAG_LIST);
    EXPECT_EQ(tag1.size(), expectedValues.size());
    EXPECT_EQ(tag2.size(), expectedValues.size());

    for (int i = 0; i < tag1.size(); ++i)
    {
        NBTLongTag& expectedTag = *((NBTLongTag*)expectedValues[i].get());
        EXPECT_EQ(tag1.get<NBTLongTag>(i).value(), expectedTag.value());
        EXPECT_EQ(tag2.get<NBTLongTag>(i).value(), expectedTag.value());
    }
}