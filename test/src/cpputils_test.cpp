#include <cpputils/binaryarchive.h>
#include <gtest/gtest.h>

class BinaryArchiveTest : public ::testing::Test {
 protected:
  virtual void Verify() {}
  virtual void SetUp() {}
  virtual void TearDown() {}
};

TEST_F(BinaryArchiveTest, SomeShit) { ASSERT_EQ(1, 1); }
