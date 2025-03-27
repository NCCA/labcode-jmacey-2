#include "Emitter.h"
#include <iostream>
#include <ngl/Random.h>
#include <algorithm>
#include <fstream>
#include <ngl/VAOPrimitives.h>
#include <ngl/Mat4.h>
#include <ngl/ShaderLib.h>
#include <ngl/Transformation.h>
#include <ngl/Util.h>
#include <ngl/VAOFactory.h>

Emitter::Emitter(size_t _num)
{
  m_maxParticles=_num;
  m_ppos.resize(m_maxParticles);
  m_pcolour.resize(m_maxParticles);
  m_pdir.resize(m_maxParticles);
  m_plife.resize(m_maxParticles);
  m_psize.resize(m_maxParticles);
  for(size_t i=0; i<m_maxParticles; ++i)
  {
    resetParticle(i);
  }

    m_vao = ngl::vaoFactoryCast<ngl::MultiBufferVAO>(
      ngl::VAOFactory::createVAO(ngl::multiBufferVAO,GL_POINTS)
      );
    m_vao->bind();
    m_vao->setData(ngl::MultiBufferVAO::VertexData(0,0)); // index 0 points
    m_vao->setData(ngl::MultiBufferVAO::VertexData(0,0)); // index 1 colours
    m_vao->unbind();
}

size_t Emitter::size() const
{
  return m_maxParticles;
}

void Emitter::update()
{
  const ngl::Vec3 gravity(0.0f,-9.81f,0.0f);
  const float dt=0.01f;

 for(size_t i=0; i<m_maxParticles; ++i)
 {
    m_pdir[i] +=gravity * dt * 0.5f;
    m_ppos[i] += m_pdir[i] * 0.5f;
    m_psize[i]+=0.01f;
    m_psize[i] = std::clamp(m_psize[i],0.0f, 2.0f);
    if(--m_plife[i] <=0 || m_ppos[i].m_y <=0.0f)
    {
      resetParticle(i);
    }
  }


}



void Emitter::resetParticle(size_t _i)
{
  ngl::Vec3 emitDir(0.0f,1.0f,0.0f);
  float spread = 5.5f;
  m_ppos[_i].set(0.0f,0.0f,0.0f);
  m_pdir[_i] = emitDir * ngl::Random::randomPositiveNumber()+randomVectorOnSphere() * spread;
  m_pdir[_i].m_y=std::abs(m_pdir[_i].m_y);
  m_psize[_i]=0.01f;
  m_plife[_i] = 20 + static_cast<int>(ngl::Random::randomPositiveNumber(100));
  m_pcolour[_i]=ngl::Random::getRandomColour3();
}


ngl::Vec3 Emitter::randomVectorOnSphere(float _radius)
{
  auto phi = ngl::Random::randomPositiveNumber(M_PI * 2.0f);
  auto costheta = ngl::Random::randomNumber();
  auto u = ngl::Random::randomPositiveNumber();
  auto theta = std::acos(costheta);
  auto r = _radius * std::cbrt(u);
  return ngl::Vec3(r * std::sin(theta) * std::cos(phi),
                   r * std::sin(theta) * std::sin(phi),
                   r * std::cos(theta));
}

void Emitter::render() const
{
  m_vao->bind();
  m_vao->setData(0,ngl::MultiBufferVAO::VertexData(
          m_ppos.size() * sizeof(ngl::Vec3),
          m_ppos[0].m_x
    ));
  m_vao->setVertexAttributePointer(0,3,GL_FLOAT,0,0);

  m_vao->setData(1,ngl::MultiBufferVAO::VertexData(
    m_pcolour.size() * sizeof(ngl::Vec3),
    m_pcolour[0].m_x
  ));

  m_vao->setVertexAttributePointer(1,3,GL_FLOAT,0,0);

  m_vao->setNumIndices(m_maxParticles);
  m_vao->draw();
  m_vao->unbind();

}