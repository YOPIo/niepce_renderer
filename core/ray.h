#ifndef _RAY_H_
#define _RAY_H_

#include "niepce.h"
#include "point3.h"
#include "vector3.h"

namespace niepce
{

class Ray
{
 public:
  Ray(){}
  virtual ~Ray(){}
  Ray(const Ray& ray) = default;
  Ray(Ray&& ray)      = default;
  Ray& operator = (const Ray& ray) = default;
  Ray& operator = (Ray&& ray)      = default;

  auto operator () (Float t) const -> Point3f
  {
    return origin + direction * t;
  }
  auto HasNaNs() const -> bool
  {
    return origin.HasNaNs() || direction.HasNaNs();
  }

 public:
  Point3f  origin;
  Vector3f direction;
};

} // namespace niepce

#endif // _RAY_H_
