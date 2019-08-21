#include "gtest/gtest.h"

namespace {

TEST(BuildTest, BreaksBuild) {
  EXPECT_EQ(0, 1);
}

}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}