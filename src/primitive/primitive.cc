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
 const std::shared_ptr <Shape>&    shape,
 const std::shared_ptr <Material>& material
) :
  shape_prt_    (shape),
  material_ptr_ (material)
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
  if (shape_prt_->IsIntersect(ray, intersection))
  {
    intersection->SetMaterial (material_ptr_);
    return true;
  }
  return false;
}
/*
// ---------------------------------------------------------------------------
*/
} // namespace niepce

