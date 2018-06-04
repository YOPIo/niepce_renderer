/*!
 * @file ray.inl
 * @brief 
 * @author Masashi Yoshida
 * @date 2018/5/5
 * @details 
 */
#include "ray.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
Ray::Ray (const Point3f& o, const Vector3f& d) :
  origin_    (o),
  direction_ (Normalize (d))
{}
/*
// ---------------------------------------------------------------------------
*/
Ray::Ray (const Ray& ray) :
  origin_    (ray.Origin ()),
  direction_ (Normalize (ray.Direction ()))
{}
/*
// ---------------------------------------------------------------------------
*/
Ray::Ray (Ray&& ray) :
  origin_    (ray.Origin ()),
  direction_ (Normalize (ray.Direction ()))
{}
/*
// ---------------------------------------------------------------------------
*/
auto Ray::operator = (const Ray& ray) -> Ray&
{
  if (this != &ray)
  {
    origin_    = ray.Origin ();
    direction_ = ray.Direction ();
  }
  return *this;
}
/*
// ---------------------------------------------------------------------------
*/
auto Ray::operator = (Ray&& ray) -> Ray&
{
  if (this != &ray)
  {
    origin_    = ray.Origin ();
    direction_ = ray.Direction ();
  }
  return *this;
}
/*
// ---------------------------------------------------------------------------
*/
auto Ray::Direction () const noexcept -> Vector3f
{
  return direction_;
}
/*
// ---------------------------------------------------------------------------
*/
auto Ray::Origin () const noexcept -> Point3f
{
  return origin_;
}
/*
// ---------------------------------------------------------------------------
*/
auto Ray::IntersectAt (Float t) const noexcept -> Point3f
{
  return origin_ + direction_ * t;
}
/*
// ---------------------------------------------------------------------------
*/
auto Ray::ToString () const noexcept -> std::string
{
  std::string res;
  res += "Origin    : " + origin_.ToString () + "\n";
  res += "Direction : " + direction_.ToString ();
  return res;
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
