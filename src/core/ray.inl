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
  direction_ (d)
{}
/*
// ---------------------------------------------------------------------------
*/
inline auto Ray::Direction () const noexcept -> Vector3f
{
  return direction_;
}
/*
// ---------------------------------------------------------------------------
*/
inline auto Ray::Origin () const noexcept -> Point3f
{
  return origin_;
}
/*
// ---------------------------------------------------------------------------
*/
inline auto Ray::IntersectAt (Float t) const noexcept -> Point3f
{
  return origin_ + direction_ * t;
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
