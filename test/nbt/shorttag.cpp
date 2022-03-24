#include <gtest/gtest.h>
#include <mc-proto/nbt/shorttag.h>

using namespace minecraft;

TEST(NBTShortTag, ReadWriteStream)
{
    mcstream stream;
    const i16 expectedVal = 0xDFC9;
    NBTShortTag tag1(expectedVal);
    tag1.write_data(stream);
    NBTShortTag tag2(stream);

    EXPECT_EQ(tag1.value(), tag2.value());
}