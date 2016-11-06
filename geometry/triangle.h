#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include <array>
#include <memory>

#include "../core/common.h"
#include "vertex.h"
#include "geometry.h"

namespace niepce
{

class Triangle : public Geometry
{
 public:
  Triangle() = default;
  Triangle(Vertex v1,
           Vertex v2,
           Vertex v3);
  Triangle(std::array<Vertex, 3>& v);
  virtual ~Triangle() = default;

  Triangle(const Triangle& t) = default;
  Triangle(Triangle&& t)      = default;
  Triangle& operator = (const Triangle& t) = default;
  Triangle& operator = (Triangle&& t)      = default;

  auto IsIntersect(const Ray& ray, HitRecord* hit_record) const -> bool;

 private:
  std::array<Vertex, 3> vertexes_;
};


}; // namespace niepce

#endif // _TRIANGLE_H_
