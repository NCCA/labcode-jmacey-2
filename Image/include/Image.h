#ifndef IMAGE_H_
#define IMAGE_H_
#include "RGBA.h"
#include <memory>
#include <string_view>

class Image
{
  public :
    Image(int _w, int _h) ;
    Image(int _w, int _h, unsigned char _r,unsigned char _g,unsigned char _b,unsigned char _a=255);
    Image(int _w, int _h, RGBA _p);

  void clear(unsigned char _r,
             unsigned char _g,
             unsigned char _b,
             unsigned char _a=255);
    void clear(RGBA _p);

    [[nodiscard]] int width() const ;
    [[nodiscard]] int height() const ;
    [[nodiscard]] RGBA getPixel(int _x, int _y) const ;
    void setPixel(int _x, int  _y, unsigned char _r,
                  unsigned char _g,
                  unsigned char _b,
                  unsigned char _a=255);
    [[nodiscard]] bool save(std::string_view _name) const;
  private:
    int m_width;
    int m_height;
    std::unique_ptr<RGBA []> m_pixels;


};

#endif
