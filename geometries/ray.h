#ifndef _RAY_H_
#define _RAY_H_

#include "../core/niepce.h"
#include "point3.h"
#include "vector3.h"

namespace niepce
{

class Ray
{
 public:
  Ray ()
  {}
  Ray (const Point3f& o, const Vector3f& dir) :
      origin(o),
      direction(dir)
  {}
  virtual ~Ray ()
  {}

  Ray (const Ray&  ray) = default;
  Ray (      Ray&& ray) = default;


  // ---------------------------------------------------------------------------
  // Ray public operator
  // ---------------------------------------------------------------------------
  Ray& operator = (const Ray&  ray) = default;
  Ray& operator = (      Ray&& ray) = default;
  auto operator () (Float t) const -> Point3f
  {
    return origin + direction * t;
  }


  // ---------------------------------------------------------------------------
  // Ray public methods
  // ---------------------------------------------------------------------------
 public:
  auto HasNaNs() const -> bool
  {
    return origin.HasNaNs() || direction.HasNaNs();
  }

  // ---------------------------------------------------------------------------
  // Ray public data
  // ---------------------------------------------------------------------------
 public:
  Point3f  origin;
  Vector3f direction;
};

class RayDifferential : public Ray
{
 public:
  RayDifferential()
  {}
  RayDifferential(const Point3f& o, const Vector3f& dir) :
      Ray(o, dir)
  {}
  virtual ~RayDifferential()
  {}

  RayDifferential(const RayDifferential& ray) = default;
  RayDifferential(RayDifferential&& ray)      = default;


  // ---------------------------------------------------------------------------
  // RayDifferential public operator
  // ---------------------------------------------------------------------------
 public:
  RayDifferential& operator = (const RayDifferential& ray) = default;
  RayDifferential& operator = (RayDifferential&& ray)      = default;


  // ---------------------------------------------------------------------------
  // RayDifferential public methods
  // ---------------------------------------------------------------------------
 public:
  auto ScaleDifferential(Float s) -> void
  {
    rx_origin    = origin + (rx_origin - origin) * s;
    ry_origin    = origin + (ry_origin - origin) * s;
    rx_direction = direction + (rx_direction - direction) * s;
    ry_direction = direction + (ry_direction - direction) * s;
  }
  auto HasNaNs() const -> bool
  {
    return Ray::HasNaNs() ||
        (has_differential && (rx_origin.HasNaNs()    || ry_origin.HasNaNs()   ||
                              rx_direction.HasNaNs() || ry_direction.HasNaNs()));
  }


  // ---------------------------------------------------------------------------
  // RayDifferentials public data
  // ---------------------------------------------------------------------------
 public:
  bool     has_differential;
  Point3f  rx_origin,    ry_origin;
  Vector3f rx_direction, ry_direction;
}; // class Ray
/*
auto operator << (std::ostream& os, const Ray& ray) -> std::ostream&
{
  os << "[origin: " << ray.origin << ", direction: " << ray.direction << "]";
  return os;
}

auto operator << (std::ostream& os, const RayDifferential& ray) -> std::ostream&
{
  os << ray;
  if (ray.has_differential)
  {
    os << "[rx orgin: " << ray.rx_origin << ", ry origin: " << ray.ry_origin << "].";
    os << "[rx direction: ]" << ray.rx_direction << ", ry direction: " << ray.ry_direction << "].";
  }
  return os;
}
*/

} // namespace niepce

#endif // _RAY_H_
