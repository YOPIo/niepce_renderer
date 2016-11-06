#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "../core/common.h"
#include "geometry.h"

namespace niepce
{

class Sphere : public Geometry
{
 public:
  Sphere() = default;
  Sphere(const glm::vec3& position, float radius);
  virtual ~Sphere() = default;

  Sphere(const Sphere& sphere) = default;
  Sphere(Sphere&& sphere)      = default;
  Sphere& operator = (const Sphere& sphere) = default;
  Sphere& operator = (Sphere&& sphere)      = default;

  auto IsIntersect(const Ray& ray, HitRecord* hit_record) const -> bool;

 private:
  glm::vec3 position_;
  float     radius_;
};


} // namespace niepce

#endif  // _SPHERE_H_
