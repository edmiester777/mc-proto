#include <gtest/gtest.h>
#include <mc-proto/nbt/stringtag.h>

using namespace minecraft;

TEST(NBTStringTag, ReadWriteStream)
{
    stringstream stream;
    NBTStringTag tag1("This is a test of encoding and decoding to/from streams.");
    tag1.write(stream);

    // checking written tag type
    uint8_t tagType;
    stream.read((char*)&tagType, sizeof(uint8_t));
    EXPECT_EQ(NBTTagTypes::TAG_STRING, tagType);

    // reading back from stream
    NBTStringTag tag2(stream);
    EXPECT_EQ(tag1.value(), tag2.value());
}