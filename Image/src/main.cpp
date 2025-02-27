#include <iostream>
#include <cstdlib>
#include "Image.h"

int main()
{
  static int w=200;
  static int h=200;
  Image img(w,h,255,255,255);
  for(int y=80; y<120; ++y)
  {
    for(int x=0; x<w; ++x)
    {
      img.setPixel(x,y,255,0,0);
    }
  }
  img.save("stripe.png");

  return EXIT_SUCCESS;
}