#include <gtest/gtest.h>
#include <mc-proto/nbt/floattag.h>

using namespace minecraft;

TEST(NBTFloatTag, ReadWriteStream)
{
    const float expectedValue = 53.55485f;
    mcstream stream;
    NBTFloatTag tag1(expectedValue);
    tag1.write_data(stream);
    NBTFloatTag tag2(stream);

    EXPECT_EQ(tag1.value(), tag2.value());
}