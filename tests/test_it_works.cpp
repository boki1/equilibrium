#include <gtest/gtest.h>

TEST(ItWorksSuite, ItWorks) {
  EXPECT_STRNE("hello", "world");
  EXPECT_EQ(7 * 6, 42);
}

