#include <gtest/gtest.h>
#include "parse_validate/checkDuplicate.h"

TEST(CheckDuplicate, FirstEventIsNotDuplicate)
{
    auto ts = std::chrono::sys_seconds{std::chrono::seconds{1000}};
    EXPECT_FALSE(checkDuplicate("id1", ts));
}

TEST(CheckDuplicate, SameEventIsDuplicate)
{

    auto ts = std::chrono::sys_seconds{std::chrono::seconds{1000}};
    EXPECT_FALSE(checkDuplicate("id1", ts));

    EXPECT_TRUE(checkDuplicate("id1", ts));
}
TEST(CheckDuplicate, DifferentEventsAreNotDuplicate)
{
    auto ts = std::chrono::sys_seconds{std::chrono::seconds{300}};
    EXPECT_FALSE(checkDuplicate("id1", ts));
    EXPECT_FALSE(checkDuplicate("id2", ts));
}
TEST(CheckDuplicate, SameEventAfterTTLIsNotDuplicate)
{
    auto ts = std::chrono::sys_seconds{std::chrono::seconds{300}};
    EXPECT_FALSE(checkDuplicate("id1", ts));
    EXPECT_FALSE(checkDuplicate("id1", ts + std::chrono::seconds{301}));
}
TEST(CheckDuplicate, BoundaryAtExactlyTTL)
{
    auto ts = std::chrono::sys_seconds{std::chrono::seconds{300}};
    EXPECT_FALSE(checkDuplicate("id1", ts));
    EXPECT_TRUE(checkDuplicate("id1", ts + std::chrono::seconds{300}));
}
TEST(CheckDuplicate, EvictsOldEvents)
{
    auto ts = std::chrono::sys_seconds{std::chrono::seconds{300}};
    EXPECT_FALSE(checkDuplicate(std::string("temp"), ts));
    EXPECT_TRUE(checkDuplicate(std::string("temp"), ts + std::chrono::seconds{300}));
}
// EXPECT_EQ(a, b);        // ==
// EXPECT_NE(a, b);        // !=
// EXPECT_LT(a, b);        // <
// EXPECT_GT(a, b);        // >
// EXPECT_TRUE(cond);
// EXPECT_FALSE(cond);
//
// EXPECT_THROW(func(), std::runtime_error);
// EXPECT_NO_THROW(func());
