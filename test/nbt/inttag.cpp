#include <gtest/gtest.h>
#include <mc-proto/nbt/inttag.h>

using namespace minecraft;

TEST(NBTIntTag, ReadWriteStream)
{
    const i32 expectedValue = 0x43F3DE;
    NBTIntTag tag1(expectedValue);
    mcstream stream;
    tag1.write_data(stream);
    NBTIntTag tag2(stream);

    EXPECT_EQ(tag1.value(), tag2.value());
}