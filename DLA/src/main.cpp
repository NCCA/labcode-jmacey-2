#include <iostream>
#include <cstdlib>
#include "Walker.h"

int main()
{
  static int width=200;
  static int height=200;
  Walker w(width,height);
  w.seed_image(10);
  int found =0;
  while(found < 1000)
  {
    auto f = w.walk();
    if(f)
    {
      found++;
    }
  }
  w.save_image("test.png");
  return EXIT_SUCCESS;
}