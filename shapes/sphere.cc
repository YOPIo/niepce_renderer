#include "sphere.h"

namespace niepce
{

Sphere::Sphere(const Transform* object_to_world,
               const Transform* world_to_object,
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

auto Sphere::LocalBoundingBox() const -> BBox3f
{
  return BBox3f();
}

auto Sphere::WorldBoundingBox() const -> BBox3f
{
  return BBox3f();
}

auto Sphere::IsIntersect(const Ray &ray, Float *t, SurfaceInteraction *surface) -> bool
{
  // Transform Ray to object space
  Ray local_ray( *world_to_local_ * ray );

  // Compute quadratic sphere coefficients and initialize parameters.
  const Float ox(local_ray.origin.x),    oy(local_ray.origin.y),    oz(local_ray.origin.z);
  const Float dx(local_ray.direction.x), dy(local_ray.direction.y), dz(local_ray.direction.z);
  const Float a(dx * dx + dy * dy + dz * dz);
  const Float b(2 * (dx * ox + dy * oy + dz * oz));
  const Float c(ox * ox + oy * oy + oz * oz - radius_ * radius_);

  // Solve quadratic equation. See P136.
  Float t0, t1;
  if ( !SolveQuadratic(a, b, c, &t0, &t1) ) { return false; }

  // Check ray direction. (_t_ should be positive.)
  if (t0 < 0.f && t1 < 0.f) { return false; }

  // Ignore reflection within a certain range.
  if (t0 < kEpsilon && t1 < kEpsilon) { return false; }

  // Initialize _t_
  *t = t0;

  // Initialize 'Surface Interaction'.
  const Point3f  hit_position = *local_to_world_ * local_ray(t0);
  const Vector3f direction    = *local_to_world_ * local_ray.direction;
  const Normal3f normal       = *local_to_world_ * (hit_position - local_ray.origin);
  // TODO: implementation
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
