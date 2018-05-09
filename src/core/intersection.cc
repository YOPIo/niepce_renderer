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
Intersection::Intersection () :
  distance_     (kInfinity),
  normal_       (),
  material_ptr_ (nullptr),
  shape_ptr_    (nullptr),
  position_     ()
{}
/*
// ---------------------------------------------------------------------------
*/
Intersection::operator bool () const noexcept
{
  if (material_ptr_ != nullptr &&
      shape_ptr_    != nullptr &&
      distance_     <  kInfinity)
  {
    return true;
  }
  return false;
}
/*
// ---------------------------------------------------------------------------
*/
auto Intersection::operator ! () const noexcept -> bool
{
  return !static_cast <bool> (*this);
}
/*
// ---------------------------------------------------------------------------
*/
auto Intersection::Distance () const noexcept -> Float
{
  return distance_;
}
/*
// ---------------------------------------------------------------------------
*/
auto Intersection::IsIntersect () const noexcept -> bool
{
  return static_cast <bool> (*this);
}
/*
// ---------------------------------------------------------------------------
*/
auto Intersection::Material ()
  const noexcept -> std::shared_ptr <niepce::Material>
{
  return material_ptr_;
}
/*
// ---------------------------------------------------------------------------
*/
auto Intersection::Normal () const noexcept -> Vector3f
{
  return normal_;
}
/*
// ---------------------------------------------------------------------------
*/
auto Intersection::Position () const noexcept -> Point3f
{
  return position_;
}
/*
// ---------------------------------------------------------------------------
*/
auto Intersection::SetDistance (Float distance) noexcept -> void
{
  this->distance_ = distance;
}
/*
// ---------------------------------------------------------------------------
*/
auto Intersection::SetMaterial
(const std::shared_ptr<niepce::Material>& material_ptr) noexcept -> void
{
  this->material_ptr_ = material_ptr;
}
/*
// ---------------------------------------------------------------------------
*/
auto Intersection::SetNormal (const Vector3f& normal) noexcept -> void
{
  this->normal_ = normal;
}
/*
// ---------------------------------------------------------------------------
*/
auto Intersection::SetShape (const std::shared_ptr<Shape>& shape) noexcept -> void
{
  this->shape_ptr_ = shape;
}
/*
// ---------------------------------------------------------------------------
*/
auto Intersection::SetPosition (const Point3f& position) noexcept -> void
{
  this->position_ = position;
}
/*
// ---------------------------------------------------------------------------
*/
} // namespace niepce
