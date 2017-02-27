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
  Ray();
  virtual ~Ray();

  Ray(const Ray& ray) = default;
  Ray(Ray&& ray)      = default;

  Ray& operator = (const Ray& ray) = default;
  Ray& operator = (Ray&& ray)      = default;

  auto operator () (Float t) const -> Point3f;
  auto HasNaNs() const -> bool;

 public:
  Point3f  origin;
  Vector3f direction;
};

class RayDifferential : public Ray
{
 public:
  RayDifferential();
  virtual ~RayDifferential();

  RayDifferential(const RayDifferential& ray) = default;
  RayDifferential(RayDifferential&& ray)      = default;

  RayDifferential& operator = (const RayDifferential& ray) = default;
  RayDifferential& operator = (RayDifferential&& ray)      = default;

  auto ScaleDifferential(Float t) -> void;
  auto HasNaNs() const -> bool;

 public:
  bool     has_differential;
  Point3f  rx_origin,    ry_origin;
  Vector3f rx_direction, ry_direction;
};

auto operator << (std::ostream& os, const Ray& ray) -> std::ostream&;
auto operator << (std::ostream& os, const RayDifferential& ray) -> std::ostream&;
} // namespace niepce

#endif // _RAY_H_
