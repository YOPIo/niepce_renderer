#ifndef _RAY_DIFFERENTIAL_H_
#define _RAY_DIFFERENTIAL_H_

#include "niepce.h"
#include "ray.h"

namespace niepce
{

class RayDifferential : public Ray
{
 public:
  RayDifferential();
  RayDifferential(const Point3f& ori, const Vector3f& dir, Float t_max = kInfinity);
  RayDifferential(const Ray& ray);
  virtual ~RayDifferential();

  RayDifferential(const RayDifferential& ray) = default;
  RayDifferential(RayDifferential&& ray)      = default;
  RayDifferential& operator = (const RayDifferential& ray) = default;
  RayDifferential& operator = (RayDifferential&& ray)      = default;

  auto ScaleDifferentials(Float s);
  auto HasNan() -> bool;

 public:
  bool     has_differentials_;
  Point3f  origin_x_, origin_y_;
  Vector3f direction_x_, direction_y_;
};

} // namespace niepce

#endif // _RAY_DIFFERENTIAL_H_
