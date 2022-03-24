#include <gtest/gtest.h>
#include <mc-proto/nbt/doubletag.h>

using namespace minecraft;

TEST(NBTDoubleTag, ReadWriteStream)
{
    const double expectedValue = -3285.3583248245;
    mcstream stream;
    NBTDoubleTag tag1(expectedValue);
    tag1.write_data(stream);
    NBTDoubleTag tag2(stream);

    EXPECT_EQ(tag1.value(), tag2.value());
}