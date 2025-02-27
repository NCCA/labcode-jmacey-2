#include <gtest/gtest.h>
#include "Image.h"
TEST(Image,ctor)
{
  const int width=1024;
  const int height=720;
  Image a(width,height);
  ASSERT_EQ(a.width(),width);
  ASSERT_EQ(a.height(),height);
}

TEST(Image,getPixel)
{
  const int width=3;
  const int height=1;
  Image a(width,height);
  auto p=a.getPixel(0,0);
  ASSERT_EQ(p.r,0);
  ASSERT_EQ(p.g,0);
  ASSERT_EQ(p.b,0);
  ASSERT_EQ(p.a,0);
}

TEST(Image,setPixel)
{
  const int width=3;
  const int height =1;
  auto a=Image(width,height);
  a.setPixel(0,0,255,0,0);
  auto pixel=a.getPixel(0,0);
  ASSERT_EQ(pixel.r,255);
  ASSERT_EQ(pixel.g,0);
  ASSERT_EQ(pixel.b,0);
  ASSERT_EQ(pixel.a,255);
  a.setPixel(1,0,0,255,0);
  pixel=a.getPixel(1,0);
  ASSERT_EQ(pixel.r,0);
  ASSERT_EQ(pixel.g,255);
  ASSERT_EQ(pixel.b,0);
  ASSERT_EQ(pixel.a,255);
  a.setPixel(2,0,0,0,255);
  pixel=a.getPixel(2,0);
  ASSERT_EQ(pixel.r,0);
  ASSERT_EQ(pixel.g,0);
  ASSERT_EQ(pixel.b,255);
  ASSERT_EQ(pixel.a,255);
  ASSERT_TRUE(a.save("rgb.png"));
}



