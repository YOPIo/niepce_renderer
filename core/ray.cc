#include "ray.h"

namespace niepce
{

Ray::Ray() : origin_(Point3f(0, 0, 0)), direction_(Vector3f(0, 0, 0)), t_max_(kInfinity)
{}

Ray::Ray(const Point3f& ori, const Vector3f& dir, Float t_max) : origin_(ori), direction_(dir), t_max_(t_max)
{}

} // namespace niepce
