#include "ray_differential.h"

namespace niepce
{

RayDifferential::RayDifferential() : has_differentials_(false)
{}

RayDifferential::RayDifferential(const Point3f& ori, const Vector3f& dir, Float t_max) :
    Ray(ori, dir, t_max), has_differentials_(false)
{}

RayDifferential::RayDifferential(const Ray& ray) : Ray(ray), has_differentials_(false)
{}

auto RayDifferential::ScaleDifferentials(Float s)
{
  origin_x_    = origin_ + (origin_x_ - origin_) * s;
  origin_y_    = origin_ + (origin_y_ - origin_) * s;
  direction_x_ = direction_ + (direction_x_ - direction_) * s;
  direction_y_ = direction_ + (direction_y_ - direction_) * s;
}

auto RayDifferential::HasNan() -> bool
{
  return Ray::HasNan() || (has_differentials_ && ( origin_x_.HasNan()   || origin_y_.HasNan() ||
                                                  direction_x_.HasNan() || direction_y_.HasNan() ));
}

} // namespace niepce
