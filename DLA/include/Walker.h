#ifndef WALKER_H_
#define WALKER_H_
#include "Image.h"
#include <memory>
#include <random>
#include <string_view>

class Walker
{
public :
    Walker(int _w, int _h);
    void save_image(std::string_view _fname) const;
    void seed_image(int _num=1);
    void reset_start();
    bool walk();
private :
    void initRNG();
    std::uniform_int_distribution<int> m_xRand;
    std::uniform_int_distribution<int> m_yRand;

    std::unique_ptr<Image> m_map;
    int m_xpos;
    int m_ypos;
};

#endif