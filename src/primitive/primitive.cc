/*!
 * @file primitive.h
 * @brief 
 * @author Masashi Yoshida
 * @date 2018/5/5
 * @details 
 */
#include "primitive.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
Primitive::Primitive
(
 const std::shared_ptr <niepce::Shape>&    shape,
 const std::shared_ptr <niepce::Material>& material
) :
  shape_prt_    (shape),
  material_ptr_ (material),
  light_ptr_    (nullptr)
{}
/*
// ---------------------------------------------------------------------------
*/
auto Primitive::IsIntersect
(
 const Ray& ray,
 Intersection *intersection
)
  const noexcept -> bool
{
  if (shape_prt_->IsIntersect (ray, intersection))
  {
    intersection->SetShape (shape_prt_);
    intersection->SetMaterial (material_ptr_);
    intersection->SetOutgoing (-Normalize (ray.Direction ()));

    return true;
  }
  return false;
}
/*
// ---------------------------------------------------------------------------
*/
auto Primitive::Shape () const noexcept -> const std::shared_ptr <niepce::Shape>
{
  return shape_prt_;
}
/*
// ---------------------------------------------------------------------------
*/
auto Primitive::Material () const noexcept
  -> const std::shared_ptr<niepce::Material>
{
  return material_ptr_;
}
/*
// ---------------------------------------------------------------------------
*/
auto Primitive::HasLight () const noexcept -> bool
{
  return (light_ptr_ != nullptr);
}
/*
// ---------------------------------------------------------------------------
*/
auto Primitive::HasMaterial () const noexcept -> bool
{
  return (material_ptr_ != nullptr);
}
/*
// ---------------------------------------------------------------------------
// Helper function for primitive
// ---------------------------------------------------------------------------
*/
auto CreatePrimitive
(
 const std::shared_ptr <Shape>&    shape,
 const std::shared_ptr <Material>& material
)
  -> std::shared_ptr <Primitive>
{
  auto primitive = std::make_shared <Primitive> (shape, material);
  return std::move (primitive);
}
/*
// ---------------------------------------------------------------------------
*/
} // namespace niepce

