#include <gtest/gtest.h>
#include <mc-proto/client.h>

using namespace minecraft;

TEST(ClientConnection, BasicAssertions)
{
    // Expect two strings not to be equal.
    EXPECT_STRNE("hello", "world");
    // Expect equality.
    EXPECT_EQ(7 * 6, 42);
}