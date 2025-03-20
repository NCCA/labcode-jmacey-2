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
  m_particles.resize(_num);
  for(auto &p : m_particles)
  {
    resetParticle(p);
  }
  m_vao = ngl::VAOFactory::createVAO(ngl::simpleVAO,GL_POINTS);
}

size_t Emitter::size() const
{
  return m_particles.size();
}

void Emitter::debug() const
{
  for (auto p: m_particles)
  {
    std::cout << p.pos.m_x << ' ' << p.pos.m_y << ' '<<p.pos.m_z<<'\n';
    std::cout << p.dir.m_x<< ' '<<p.dir.m_y<<' '<<p.dir.m_z<<'\n';
    std::cout<< p.colour.m_x<<' '<<p.colour.m_y<<' '<<p.colour.m_z<<'\n';
    std::cout<< p.life<<' '<<p.size<<'\n';
  }
}
void Emitter::update()
{
  const ngl::Vec3 gravity(0.0f,-9.81f,0.0f);
  const float dt=0.01;

  for(auto &p : m_particles)
  {
    p.dir +=gravity * dt * 0.5f;
    p.pos += p.dir * 0.5f;
    p.size+=0.01f;
    p.size = std::clamp(p.size,0.0f, 2.0f);
    if(--p.life <=0 || p.pos.m_y <=0.0f)
    {
      resetParticle(p);
    }
  }


}



void Emitter::resetParticle(Particle &io_p)
{
  ngl::Vec3 emitDir(0.0f,1.0f,0.0f);
  float spread = 5.5f;
  io_p.pos.set(0.0f,0.0f,0.0f);
  io_p.dir = emitDir * ngl::Random::randomPositiveNumber()+randomVectorOnSphere() * spread;
  io_p.dir.m_y=std::abs(io_p.dir.m_y);
  io_p.size=0.01f;
  io_p.life = 20 + static_cast<int>(ngl::Random::randomPositiveNumber(100));
  io_p.colour=ngl::Random::getRandomColour3();

}

void Emitter::writeGeo(std::string_view _fname) const
{
  auto file=std::ofstream(_fname.data());
  file<<"PGEOMETRY V5 \n";
  file<<"NPoints "<<m_particles.size() <<" NPrims 1 \n";
  file<<"NPointGroups 0 NPrimGroups 0 \n";
  file<<"NPointAttrib 2 NVertexAttrib 0 NPrimAttrib 0 NAttrib 0 \n";
  file<<"PointAttrib \n";
  file<<"Cd 3 float 1 1 1 \n";
  file<<"pscale 1 float 0.5 \n";
  for(auto p : m_particles)
  {
    file<< p.pos.m_x<<' '<<p.pos.m_y<<' '<<p.pos.m_z<<" 1 (";
    file<< p.colour.m_x<<' '<<p.colour.m_y<<' '<<p.colour.m_z<< ' ';
    file<< p.size <<" )\n";
  }
  file<<"Part "<< m_particles.size()<<' ';
  for(size_t i=0; i<m_particles.size(); ++i)
  {
    file << i << ' ';
  }
  file <<"[0] \n";
  file<<"beginExtra\n";
  file<<"endExtra\n";
  file.close();
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
  std::cout<<"Render\n";
  auto view = ngl::lookAt({0,20,20},{0,0,0},{0,1,0});
  auto project = ngl::perspective(45.0f,1.0f,0.1f,200.0f);
  ngl::ShaderLib::use(ngl::nglColourShader);
  ngl::ShaderLib::setUniform("MVP",project*view);
  glPointSize(10.0);
  m_vao->bind();
  m_vao->setData(ngl::AbstractVAO::VertexData(
          m_particles.size() * sizeof(Particle),
          m_particles[0].pos.m_x
    ));
  m_vao->setVertexAttributePointer(0,3,GL_FLOAT,sizeof(Particle),0);
  m_vao->setNumIndices(m_particles.size());
  m_vao->draw();
  m_vao->unbind();
//  ngl::Transformation tx;
//  for(auto p : m_particles)
//  {
//    tx.setPosition(p.pos);
//    //tx.setScale(p.size,p.size,p.size);
//    ngl::ShaderLib::setUniform("MVP", project*view*tx.getMatrix());
//    ngl::ShaderLib::setUniform("Colour",p.colour.m_r,p.colour.m_g,p.colour.m_b,1.0f);
//
//    ngl::VAOPrimitives::draw("sphere",GL_POINTS);
//  }

}