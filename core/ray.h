#ifndef _RAY_H_
#define _RAY_H_

//#include "../3rdparty/glm/glm.hpp"
#include "niepce.h"
#include "vector3.h"
#include "normal3.h"
#include "point3.h"

namespace niepce
{

class Ray
{
 public:
  Ray();
  Ray(const Point3f& ori, const Vector3f& dir, Float t_max = kinfinity);
  virtual ~Ray() = default;

  Ray(const Ray& ray) = default;
  Ray(Ray&& ray)      = default;
  Ray& operator = (const Ray& ray) = default;
  Ray& operator = (Ray&& ray)      = default;

  auto operator () (Float t) const -> Point3f
  {
    return ori_ + t * dir_;
  }
  auto HasNan() -> bool
  {
    return ori_.HasNan() || dir_.HasNan() || IsNan(t_max_);
  }

 public:
  Point3f  origin_;
  Vector3f direction_;
  mutable Float t_max_;
};

} // namespace niepce

#endif // _RAY_H_
