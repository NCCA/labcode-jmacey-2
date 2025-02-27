
#include <gtest/gtest.h>
#include "RGBA.h"

int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc,argv);
  return RUN_ALL_TESTS();
}

TEST(RGBA,construct)
{
  RGBA a;
  ASSERT_TRUE(a.r == 0);
  ASSERT_TRUE(a.g == 0);
  ASSERT_TRUE(a.b == 0);
  ASSERT_TRUE(a.a == 0);
}

TEST(RGBA,constructvales)
{
  auto a=RGBA(255,0,128,57);
  EXPECT_EQ(a.r,255);
  EXPECT_TRUE(a.g == 0);
  EXPECT_EQ(a.b,128);
  EXPECT_EQ(a.a,57);
}

// Test pixel union
TEST(RGBA, PixelUnion)
{
  RGBA color(255, 128, 64, 32);
  uint32_t expectedPixels = (32 << 24) | (64 << 16) | (128 << 8) | 255;
  EXPECT_EQ(color.pixels, expectedPixels);
}

TEST(RGBA,set)
{
  auto a=RGBA();
  a.set(0,255,0,255);
  EXPECT_EQ(a.r,0);
  EXPECT_EQ(a.g,255);
  EXPECT_EQ(a.b,0);
  EXPECT_EQ(a.a,255);
}

TEST(RGBA,clamp)
{
  RGBA a(255,127,55,0);

  a.clamp(56,128);
  EXPECT_EQ(a.r,128);
  EXPECT_EQ(a.g,127);
  EXPECT_EQ(a.b,56);
  EXPECT_EQ(a.a,56);
}