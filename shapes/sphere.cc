#include "sphere.h"

namespace niepce
{


// ---------------------------------------------------------------------------
// Constructors
// ---------------------------------------------------------------------------
Sphere::Sphere() :
    Shape(),
    radius_(1.0)
{}

Sphere::Sphere(const std::shared_ptr<Transform>& local_to_world,
               const std::shared_ptr<Transform>& world_to_local,
               Float radius) :
    Shape(local_to_world, world_to_local),
    radius_(radius)
{}

Sphere::~Sphere()
{}


// ---------------------------------------------------------------------------
// Sphere public override methods
// ---------------------------------------------------------------------------
auto Sphere::SurfaceArea () const -> Float
{
  return 4 * kPi * radius_ * radius_;
}

auto Sphere::LocalBounds () const -> Bounds3f
{
  return Bounds3f();
}

auto Sphere::WorldBounds () const -> Bounds3f
{
  return Bounds3f();
}

auto Sphere::IsIntersect (const Ray&   ray,
                          Interaction* inter) const -> bool
{
  // Transform Ray to object space
  Ray local_ray = Ray(*world_to_local_ * ray );

  // Compute quadratic sphere coefficients and initialize parameters.
  const Float ox(local_ray.origin.x),    oy(local_ray.origin.y),    oz(local_ray.origin.z);
  const Float dx(local_ray.direction.x), dy(local_ray.direction.y), dz(local_ray.direction.z);
  const Float a(dx * dx + dy * dy + dz * dz);
  const Float b(2 * (dx * ox + dy * oy + dz * oz));
  const Float c(ox * ox + oy * oy + oz * oz - radius_ * radius_);

  // Solve quadratic equation. See P136 PBR.
  Float t0, t1;
  if ( !SolveQuadratic(a, b, c, &t0, &t1) ) { return false; }

  // Check ray direction. (_t_ should be positive.)
  if (t0 < 0.f && t1 < 0.f) { return false; }

  // Ignore reflection within a certain range.
  if (t0 < kEpsilon && t1 < kEpsilon) { return false; }

  // Initialize 'Surface Interaction'.
  const Point3f  hit_position = *local_to_world_ * local_ray(t0);
  const Vector3f direction    = *local_to_world_ * local_ray.direction;
  const Normal3f normal       = *local_to_world_ * (hit_position - local_ray.origin);

  // Store interaction data
  *inter = Interaction(t0, hit_position, direction, normal);

  return true;
}


}  // namespace niepce
