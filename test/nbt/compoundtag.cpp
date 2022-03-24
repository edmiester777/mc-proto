#include <gtest/gtest.h>
#include <mc-proto/nbt/nbt.h>

using namespace minecraft;

TEST(NBTCompoundTag, ReadWriteComplexStream)
{
    NBTCompoundTag tag1("name", {
        {"BYTE", NBTTagPtr(new NBTByteTag(0xFF))},
        {"LONG", NBTTagPtr(new NBTLongTag(104842l))},
        {"LONGARRAY", NBTTagPtr(new NBTLongArrayTag({
            1,
            2,
            3,
            4,
            5,
            103853
        }))},
        {"COMPOUND", NBTTagPtr(new NBTCompoundTag("SUBCOMPOUND", {
            {"DOUBLE", NBTTagPtr(new NBTDoubleTag(242.48284))}
        }))},
     });
    mcstream stream;
    tag1.write_data(stream);
    NBTCompoundTag tag2(stream);

    EXPECT_EQ(TAG_COMPOUND, tag1.type());
    EXPECT_EQ(tag1.size(), tag2.size());
    EXPECT_EQ(tag1.name(), tag2.name());
    EXPECT_EQ(tag1.get<NBTByteTag>("BYTE").value(), tag2.get<NBTByteTag>("BYTE").value());
    EXPECT_EQ(tag1.get<NBTLongTag>("LONG").value(), tag2.get<NBTLongTag>("LONG").value());
    EXPECT_EQ(tag1.get<NBTLongArrayTag>("LONGARRAY").size(), tag2.get<NBTLongArrayTag>("LONGARRAY").size());
    EXPECT_TRUE(tag2.contains("COMPOUND"));
}