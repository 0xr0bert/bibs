#include "bibs.hpp"
#include <gtest/gtest.h>

TEST(SquareRootTest, Positive) {
  ASSERT_EQ(10, squareRoot(100.0));
  ASSERT_EQ(0, squareRoot(0.0));
}

TEST(SquareRootTest, Negative) { ASSERT_EQ(-1.0, squareRoot(-16.0)); }

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
