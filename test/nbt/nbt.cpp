#include <gtest/gtest.h>
#include <mc-proto/nbt/nbt.h>
#include <fstream>
#include <zlib.h>

using namespace minecraft;

TEST(NBT, HelloWorldTest)
{
    ifstream stream(_CMAKE_PROJECT_PATH "/test/nbt/hello_world.nbt", ifstream::in);

    NBTTagPtr rootTag = read_nbt_from_stream(stream);

    EXPECT_EQ(rootTag->type(), TAG_COMPOUND);
}