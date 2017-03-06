#include "sphere.h"

namespace niepce
{

Sphere::Sphere(const std::shared_ptr<Transform>& object_to_world,
               const std::shared_ptr<Transform>& world_to_object,
               const Float radius) :
    Shape(object_to_world, world_to_object),
    radius_(radius)
{}

Sphere::~Sphere()
{}

auto Sphere::SurfaceArea() const -> Float
{

}

auto Sphere::ObjectBound() const -> BBox3f
{

}

auto Sphere::IsIntersect(const Ray &ray, Float *t, SurfaceInteraction *surface) -> bool
{
  // Transform Ray to object space
  Ray obj_ray( *world_to_object_ * ray );

  // Compute quadratic sphere coefficients
  // Todo: Floating-point rounding error

  // Initialize parameters
  const Float ox(ray.origin.x),    oy(ray.origin.y),    oz(ray.origin.z);
  const Float dx(ray.direction.x), dy(ray.direction.y), dz(ray.direction.z);
  const Float a(dx * dx + dy * dy + dz * dz);
  const Float b(2 * (dx * ox + dy * oy + dz * oz));
  const Float c(ox * ox + oy * oy + oz * oz - radius_ * radius_);

  // Solve quadratic equation for t
  // See P136
  Float t0, t1;
  if ( SolveQuadratic(a, b, c, &t0, &t1) ) { return false; } // See P1079

  const Point3f p_hit( ray(t0) );

  return true;
}

}  // namespace niepce
