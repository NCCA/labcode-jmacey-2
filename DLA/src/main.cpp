#include <iostream>
#include <cstdlib>
#include "Walker.h"
#include <fmt/format.h>
int main()
{
  static int width=400;
  static int height=400;
  Walker w(width,height);
  w.seed_image(25);
  int found =0;
  int frame_number=0;
  for(size_t i=0; i<100000; ++i)
  {
    if(w.walk())
    {
      if((i%100) == 0)
      {
        w.save_image(fmt::format("/transfer/DLA/DLA.{:04d}.jpg",frame_number++));
      }
    }
  }

  return EXIT_SUCCESS;
}