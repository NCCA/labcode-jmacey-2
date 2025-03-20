#ifndef EMITTER_H_
#define EMITTER_H_
#include <vector>
#include <string_view>
#include "Particle.h"
#include <ngl/Vec3.h>
#include <ngl/AbstractVAO.h>
#include <memory>
class Emitter
{
public :
    Emitter(size_t _num);
    size_t size() const;
    void debug() const;
    void update();
    void render() const;
    void writeGeo(std::string_view _fname) const;
private :
    std::vector<Particle> m_particles;
    void resetParticle(Particle &io_p);
    ngl::Vec3 randomVectorOnSphere(float _radius = 1.0f);
    std::unique_ptr<ngl::AbstractVAO> m_vao;
};

#endif