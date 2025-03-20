#include "Image.h"
#include <OpenImageIO/imageio.h>
Image::Image(int _w, int _h) : m_width{_w},
                              m_height{_h}
{
 m_pixels = std::make_unique<RGBA []>(m_width*m_height);
}

Image::Image(int _w, int _h, unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a) :
Image(_w,_h)
{
  clear(_r,_g,_b,_a);
}

Image::Image(int _w, int _h, RGBA _p) : Image(_w,_h)
{
  clear(_p);
}


void Image::clear(RGBA _p)
{
  for(size_t i=0; i<m_width*m_height; ++i)
  {
    m_pixels[i]=_p;
  }
}

void Image::clear(unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a)
{
  auto p=RGBA(_r,_g,_b,_a);
  clear(p);
}

RGBA Image::getPixel(int _x, int _y) const
{
  size_t index = (_y*m_width) + _x;
  return m_pixels[index];
}

void Image::setPixel(int _x, int _y, unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a)
{
  size_t index = (_y*m_width) + _x;
  m_pixels[index]=RGBA(_r,_g,_b,_a);

}

bool Image::save(std::string_view _name) const
{
  using namespace OIIO;
  auto out = ImageOutput::create(_name);
  ImageSpec spec(m_width,m_width,4,TypeDesc::UINT8);
  bool success = out->open(_name.data(),spec);
  success = out->write_image(TypeDesc::UINT8,m_pixels.get());
  success = out->close();
  return success;
}


int Image::width() const
{
  return m_width;
}

int Image::height() const
{
  return m_height;
}






