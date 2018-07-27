/*!
 * @file sphere.cc
 * @brief 
 * @author Masashi Yoshida
 * @date 2018/5/5
 * @details 
 */
#include "sphere.h"
#include "../core/ray.h"
#include "../core/point2f.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
Sphere::Sphere (const Transform &local_to_world, Float radius) :
  Shape   (local_to_world),
  radius_ (radius)
{}
/*
// ---------------------------------------------------------------------------
*/
auto Sphere::IsIntersect
(
 const Ray& ray,
 Intersection* intersection
)
  const noexcept -> bool
{
  const auto center = local_to_world_ * Point3f::Zero ();

  const auto op = center - ray.Origin ();
  const auto b  = Dot (op, ray.Direction ());
  const auto c  = b * b - Dot (op, op) + radius_ * radius_;

  if (c < 0.0) { return false; }

  const auto sqrt_c = std::sqrt (c);
  const auto t1 = b - sqrt_c;
  const auto t2 = b + sqrt_c;

  if (t1 < kIntersectionEpsilon && t2 < kIntersectionEpsilon) { return false; }

  const auto t = t1 > kIntersectionEpsilon ? t1 : t2;

  // Compute hit position and normal in local coordinate.
  const auto position = ray.IntersectAt (t);
  const auto normal   = Normalize (position - center);

  // Spherical mapping.
  const auto u = std::atan2 (normal.X (), normal.Z ()) / (2.0 * kPi) + 0.5;
  const auto v = 1.0 - (std::acos (normal.Y ()) / kPi);

  intersection->SetDistance (t);
  intersection->SetPosition (position);
  intersection->SetNormal   (normal);
  intersection->SetTexcoord (Point2f (u, v));

  return true;

  /*
  const auto local_ray = world_to_local_ * ray;

  const auto op = Point3f::Zero () - local_ray.Origin ();
  const auto b  = Dot (op, local_ray.Direction ());
  const auto c  = b * b - Dot (op, op) + radius_ * radius_;

  if (c < 0.0) { return false; }

  const auto sqrt_c = std::sqrt (c);
  const auto t1 = b - sqrt_c;
  const auto t2 = b + sqrt_c;

  if (t1 < kIntersectionEpsilon && t2 < kIntersectionEpsilon) { return false; }

  const auto t = t1 > kIntersectionEpsilon ? t1 : t2;

  // Compute hit position and normal in local coordinate.
  const auto position = local_ray.IntersectAt (t);
  const auto normal   = Normalize (position - Point3f::Zero ());

  // Spherical mapping.
  const auto u = std::atan2 (normal.X (), normal.Z ()) / (2.0 * kPi) + 0.5;
  const auto v = 1.0 - (std::acos (normal.Y ()) / kPi);

  intersection->SetDistance ((position - local_ray.Origin ()).Length ());
  intersection->SetPosition (local_to_world_ * position);
  intersection->SetNormal   (Normalize (normal));
  intersection->SetTexcoord (Point2f (u, v));

  return true;
  */
}
/*
// ---------------------------------------------------------------------------
*/
auto Sphere::Bounds () const noexcept -> Bounds3f
{
  const auto min = local_to_world_ * Point3f (-radius_, -radius_, -radius_);
  const auto max = local_to_world_ * Point3f ( radius_,  radius_,  radius_);
  return Bounds3f (min, max);
}
/*
// ---------------------------------------------------------------------------
*/
auto Sphere::Sample (const Point2f& sample) const noexcept -> Point3f
{
    return Point3f ();
}
/*
// ---------------------------------------------------------------------------
*/
auto Sphere::SurfaceArea () const noexcept -> Float
{
  return 4 * kPi * radius_ * radius_;
}
/*
// ---------------------------------------------------------------------------
// Helper function for sphere
// ---------------------------------------------------------------------------
*/
auto CreateSphere
(
 const Transform &transform,
 Float radius
)
  -> std::shared_ptr <Shape>
{
  std::shared_ptr <Shape> sphere (new Sphere (transform, radius));
  return std::move (sphere);
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
