/*!
 * @file sphere.cc
 * @brief 
 * @author Masashi Yoshida
 * @date 2018/5/5
 * @details 
 */
#include "sphere.h"
#include "../core/ray.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
Sphere::Sphere (Float radius, const Point3f& position) :
  radius_ (radius),
  center_ (position)
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
  const Float kSphereEpsilon = 1e-4;

  const Vector3f op = center_ - ray.Origin ();
  const Float    b  = Dot (op, ray.Direction ());
  const Float    c  = b * b - Dot (op, op) + radius_ * radius_;

  if (c < 0.0) { return false; }

  const Float sqrt_c = std::sqrt (c);
  const Float t1 = b - sqrt_c;
  const Float t2 = b + sqrt_c;

  if (t1 < kSphereEpsilon && t2 < kSphereEpsilon) { return false; }

  const Float    distance = t1 > kSphereEpsilon ? t1 : t2;
  const Point3f  position = ray.IntersectAt (distance);
  const Vector3f normal   = Normalize (position - center_);

  intersection->SetDistance (distance);
  intersection->SetNormal   (normal);
  intersection->SetPosition (position);

  return true;
}
/*
// ---------------------------------------------------------------------------
// Helper function for sphere
// ---------------------------------------------------------------------------
*/
auto CreateSphere
(
 const Point3f& position,
 Float radius
)
  -> std::shared_ptr <Shape>
{
  std::shared_ptr <Shape> sphere (new Sphere (radius, position));
  return std::move (sphere);
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
