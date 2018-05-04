/*!
 * @file intersection.h
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#include "intersection.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
inline Intersection::Intersection () :
  distance_     (kInfinity),
  normal_       (),
  material_ptr_ (nullptr),
  position_     ()
{}
/*
// ---------------------------------------------------------------------------
*/
inline Intersection::operator bool () const noexcept
{
  if (material_ptr_ != nullptr &&
      distance_     <  kInfinity)
  {
    return true;
  }
  return false;
}
/*
// ---------------------------------------------------------------------------
*/
inline auto Intersection::operator ! () const noexcept -> bool
{
  return !static_cast <bool> (*this);
}
/*
// ---------------------------------------------------------------------------
*/
inline auto Intersection::Distance () const noexcept -> Float
{
  return distance_;
}
/*
// ---------------------------------------------------------------------------
*/
inline auto Intersection::IsIntersect () const noexcept -> bool
{
  return static_cast <bool> (*this);
}
/*
// ---------------------------------------------------------------------------
*/
inline auto Intersection::Material ()
  const noexcept -> std::shared_ptr <niepce::Material>
{
  return material_ptr_;
}
/*
// ---------------------------------------------------------------------------
*/
inline auto Intersection::Normal () const noexcept -> Vector3f
{
  return normal_;
}
/*
// ---------------------------------------------------------------------------
*/
inline auto Intersection::Position () const noexcept -> Point3f
{
  return position_;
}
/*
// ---------------------------------------------------------------------------
*/
inline auto Intersection::SetDistance (Float distance) noexcept -> void
{
  this->distance_ = distance;
  if (this->distance_ < kInfinity) { is_hit_ = true; }
}
/*
// ---------------------------------------------------------------------------
*/
inline auto Intersection::SetMaterial
(const std::shared_ptr<niepce::Material>& material_ptr) noexcept -> void
{
  this->material_ptr_ = material_ptr;
}
/*
// ---------------------------------------------------------------------------
*/
inline auto Intersection::SetNormal (const Vector3f& normal) noexcept -> void
{
  this->normal_ = normal;
}
/*
// ---------------------------------------------------------------------------
*/
inline auto Intersection::SetPosition (const Point3f& position) noexcept -> void
{
  this->position_ = position;
}
/*
// ---------------------------------------------------------------------------
*/
} // namespace niepce
