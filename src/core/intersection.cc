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
  const noexcept -> const std::shared_ptr <niepce::Material>
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
auto Intersection::Outgoing () const noexcept -> Ray
{
  return outgoing_;
}
/*
// ---------------------------------------------------------------------------
*/
auto Intersection::Shape ()
  const noexcept -> const std::shared_ptr <niepce::Shape>
{
  return shape_ptr_;
}
/*
// ---------------------------------------------------------------------------
*/
auto Intersection::Texcoord () const noexcept -> Point2f
{
  return texcoord_;
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
auto Intersection::SetOutgoing (const Ray &ray) noexcept -> void
{
  this->outgoing_ = ray;
}
/*
// ---------------------------------------------------------------------------
*/
auto Intersection::SetShape
(const std::shared_ptr <niepce::Shape>& shape)
noexcept -> void
{
  this->shape_ptr_ = shape;
}
/*
// ---------------------------------------------------------------------------
*/
auto Intersection::SetTexcoord (const Point2f& texcoord) noexcept -> void
{
  this->texcoord_ = texcoord;
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
