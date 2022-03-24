#include <gtest/gtest.h>
#include <mc-proto/nbt/nbt.h>
#include <fstream>

using namespace minecraft;

TEST(NBT, HelloWorldTest)
{
    ifstream fstream(_CMAKE_PROJECT_PATH "/test/nbt/hello_world.nbt", ios::binary | ios::ate);
    fstream.seekg(0, ios::beg);
    safebytebuffer buf;
    fstream >> buf;
    mcstream stream;
    stream << buf;

    NBTTagPtr rootTag = read_nbt_from_stream(stream);

    EXPECT_EQ(rootTag->type(), TAG_COMPOUND);
    
    NBTCompoundTag* compound = (NBTCompoundTag*)rootTag.get();
    EXPECT_EQ(compound->name(), "hello world");
    EXPECT_EQ(compound->get<NBTStringTag>("name").value(), "Bananrama");
}