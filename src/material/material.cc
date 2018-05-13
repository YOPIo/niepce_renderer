/*!
 * @file material.cc
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#include "material.h"
#include "../core/pixel.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
Material::Material () :
  emission_ (nullptr)
{}
/*
// ---------------------------------------------------------------------------
*/
Material::Material (const std::shared_ptr <Texture>& emission) :
  emission_ (emission)
{}
/*
// ---------------------------------------------------------------------------
*/
auto Material::HasEmission () const noexcept -> bool
{
  return static_cast <bool> (emission_);
}
/*
// ---------------------------------------------------------------------------
*/
auto Material::Emission (const Point2f& uv) const noexcept -> Vector3f
{
  if (emission_)
  {
    return emission_->Sample (uv);
  }
  return Vector3f::Zero ();
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/

