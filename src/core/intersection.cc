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
  position_     (),
  is_hit_       (false)
{}
/*
// ---------------------------------------------------------------------------
*/
Intersection::operator bool () const noexcept
{
  return is_hit_;
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
auto Intersection::Binormal () const noexcept -> Vector3f
{
  return binormal_;
}
/*
// ---------------------------------------------------------------------------
*/
auto Intersection::Tangent () const noexcept -> Vector3f
{
  return tangent_;
}
/*
// ---------------------------------------------------------------------------
*/
auto Intersection::Outgoing () const noexcept -> Vector3f
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

  // Calculate the tangent vector and binormal vector from new normal.
  BuildOrthonormalBasis (normal_, &tangent_, &binormal_);
}
/*
// ---------------------------------------------------------------------------
*/
auto Intersection::SetOutgoing (const Vector3f& outgoing) noexcept -> void
{
  this->outgoing_ = outgoing;
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
auto Intersection::SampledBsdfType () const noexcept -> BsdfType
{
  return type_;
}
/*
// ---------------------------------------------------------------------------
*/
auto Intersection::SetBsdfType (BsdfType type) noexcept -> void
{
  type_ = type;
}
/*
// ---------------------------------------------------------------------------
*/
auto Intersection::MakeHitFlagFalse () noexcept -> void
{
  is_hit_ = false;
}
/*
// ---------------------------------------------------------------------------
*/
auto Intersection::MakeHitFlagTrue () noexcept -> void
{
  is_hit_ = true;
}
/*
// ---------------------------------------------------------------------------
*/
auto Intersection::ToLocal (const Vector3f& v) const noexcept -> Vector3f
{
  return Vector3f (Dot (v, tangent_),
                   Dot (v, binormal_),
                   Dot (v, normal_));
}
/*
// ---------------------------------------------------------------------------
*/
auto Intersection::ToWorld (const Vector3f& v) const noexcept -> Vector3f
{
  return Vector3f
    (v.X () * tangent_.X () + v.Y () * binormal_.X () + v.Z () * normal_.X (),
     v.X () * tangent_.Y () + v.Y () * binormal_.Y () + v.Z () * normal_.Y (),
     v.X () * tangent_.Z () + v.Y () * binormal_.Z () + v.Z () * normal_.Z ());
}
/*
// ---------------------------------------------------------------------------
*/
} // namespace niepce
