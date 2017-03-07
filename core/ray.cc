#include "ray.h"

namespace niepce
{

Ray::Ray()
{}

Ray::Ray(const Point3f& o, const Vector3f& dir) :
    origin(o), direction(dir)
{}

Ray::~Ray()
{}

auto Ray::operator () (Float t) const -> Point3f
{
  return origin + direction * t;
}

auto Ray::HasNaNs() const -> bool
{
  return origin.HasNaNs() || direction.HasNaNs();
}

RayDifferential::RayDifferential() : has_differential(false)
{}

RayDifferential::RayDifferential(const Point3f& o, const Vector3f& dir) :
    Ray(o, dir)
{}

RayDifferential::~RayDifferential()
{}

auto RayDifferential::ScaleDifferential(Float s) -> void
{
  rx_origin    = origin + (rx_origin - origin) * s;
  ry_origin    = origin + (ry_origin - origin) * s;
  rx_direction = direction + (rx_direction - direction) * s;
  ry_direction = direction + (ry_direction - direction) * s;
}

auto RayDifferential::HasNaNs() const -> bool
{
  return Ray::HasNaNs() ||
         (has_differential && (rx_origin.HasNaNs()    || ry_origin.HasNaNs()   ||
                               rx_direction.HasNaNs() || ry_direction.HasNaNs()));
}

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

} // namespace niepce
