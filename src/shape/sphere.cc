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
  // TODO: Localで計算する
  const auto center = local_to_world_ * Point3f::Zero ();
  const auto po = center - ray.Origin ();

  const auto b = Dot (po, ray.Direction ());
  const auto discr = b * b - Dot (po, po) + radius_ * radius_;

  if (discr < 0.0) { return false; }

  const auto sqrt_discr = std::sqrt (discr);
  const auto t1 = b - sqrt_discr;
  const auto t2 = b + sqrt_discr;

  if (t1 < kEpsilon && t2 < kEpsilon) { return false; }

  const auto t = t1 > kEpsilon ? t1 : t2;
  const auto p = ray.Origin () + t * ray.Direction ();
  const auto n = Normalize (p - center);

  const auto tmp = Normalize (world_to_local_ * p - Point3f::Zero ());
  const auto theta = std::acos (tmp.Y () / radius_);
  auto phi = std::atan2 (tmp.X (), tmp.Z ());
  if (phi < 0.0) { phi += 2.0 * kPi; }
  auto u = 1.0 - (phi / (2.0 * kPi));
  auto v = (theta / kPi);

  intersection->SetDistance (t);
  intersection->SetPosition (p);
  intersection->SetNormal   (n);
  intersection->SetTexcoord (Point2f (u, v));

  return true;
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
