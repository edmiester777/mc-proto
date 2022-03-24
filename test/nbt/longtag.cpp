#include <gtest/gtest.h>
#include <mc-proto/nbt/longtag.h>

using namespace minecraft;

TEST(NBTLongTag, ReadWriteStream)
{
    i64 expectedValue = 0x6512F5DE9F4D520F;
    mcstream stream;
    NBTLongTag tag1(expectedValue);
    tag1.write_data(stream);
    NBTLongTag tag2(stream);
    EXPECT_EQ(tag1.value(), tag2.value());
}