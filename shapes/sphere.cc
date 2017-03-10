#include "sphere.h"

namespace niepce
{

Sphere::Sphere(const std::shared_ptr<Transform>& object_to_world,
               const std::shared_ptr<Transform>& world_to_object,
               Float radius) :
    Shape(object_to_world, world_to_object),
    radius_(radius)
{}

Sphere::~Sphere()
{}

auto Sphere::SurfaceArea() const -> Float
{
  return 4 * kPi * radius_ * radius_;
}

auto Sphere::ObjectBound() const -> BBox3f
{
  return BBox3f();
}

auto Sphere::IsIntersect(const Ray &ray, Float *t, SurfaceInteraction *surface) -> bool
{
  // Transform Ray to object space
  Ray obj_ray( *world_to_local_ * ray );

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
  if ( !SolveQuadratic(a, b, c, &t0, &t1) ) { return false; }

  const Point3f  hit_position = *local_to_world_ * obj_ray(t0);
  const Vector3f direction    = *local_to_world_ * obj_ray.direction;
  const Normal3f normal       = *local_to_world_ * (hit_position - obj_ray.origin);

  const Point2f  uv;
  const Vector2f dpdu;
  const Vector2f dpdv;
  const Normal3f dndu;
  const Normal3f dndv;

  *surface = SurfaceInteraction(hit_position, direction,
                                normal,       uv,
                                dpdu,         dpdv,
                                dndu,         dndv);
  return true;
}

auto Sphere::CenterInWorld() const -> Point3f
{
  return  *local_to_world_ * Point3f(0, 0, 0);
}

auto Sphere::CenterInLocal() const -> Point3f
{
  return Point3f(0, 0, 0);
}

}  // namespace niepce
