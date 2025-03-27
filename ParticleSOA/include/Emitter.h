#ifndef EMITTER_H_
#define EMITTER_H_
#include <vector>
#include <string_view>
#include "Particle.h"
#include <ngl/Vec3.h>
#include <ngl/MultiBufferVAO.h>
#include <memory>
class Emitter
{
public :
    Emitter(size_t _num);
    size_t size() const;
    void update();
    void render() const;
private :
    std::vector<ngl::Vec3> m_ppos;
    std::vector<ngl::Vec3> m_pdir;
    std::vector<ngl::Vec3> m_pcolour;
    std::vector<float> m_psize;
    std::vector<int> m_plife;
    size_t m_maxParticles;
    void resetParticle(size_t _i);
    ngl::Vec3 randomVectorOnSphere(float _radius = 1.0f);
    std::unique_ptr<ngl::MultiBufferVAO> m_vao;
};

#endif