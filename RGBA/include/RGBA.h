#ifndef RGBA_H_
#define RGBA_H_

#include <cstdint>
#include <algorithm>
struct RGBA
{
  RGBA()=default;
  RGBA(unsigned char _r,unsigned char _g , unsigned char _b, unsigned char _a) :
  r{_r},g{_g},b{_b},a{_a} {}

  void set(unsigned char _r,unsigned char _g , unsigned char _b, unsigned char _a)
  {
    r=_r;
    g=_g;
    b=_b;
    a=_a;
  }

  // std::clamp   r=std::clamp(r,low,hi);
  void clamp(unsigned char _min, unsigned char _max)
  {
    r=std::clamp(r,_min,_max);
    g=std::clamp(g,_min,_max);
    b=std::clamp(b,_min,_max);
    a=std::clamp(a,_min,_max);

  }

  union
  {
      uint32_t pixels=0;
      struct
      {
         unsigned char r;
         unsigned char g;
         unsigned char b;
         unsigned char a;
      };
  };

};

#endif