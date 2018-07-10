/*!
 * @file material.cc
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#include "material.h"
#include "../core/attributes.h"
#include "../core/material_attributes.h"
#include "../core/vector3f.h"
#include "../core/pixel.h"
#include "../material/matte.h"
#include "../material/metal.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
Material::Material (const std::shared_ptr <Texture <Spectrum>>& emission) :
  emission_ (emission)
{}
/*
// ---------------------------------------------------------------------------
*/
auto Material::HasEmission () const noexcept -> bool
{
  if (emission_ != nullptr)
  {
    return !emission_->IsBlack ();
  }
  return false;
}
/*
// ---------------------------------------------------------------------------
*/
auto Material::Emission (const Intersection& isect) const noexcept -> Spectrum
{
  if (emission_)
  {
    return emission_->Evaluate (isect);
  }
  return Vector3f (0);
}
/*
// ---------------------------------------------------------------------------
*/
auto CreateMaterial (const MaterialAttributes& attributes)
  -> std::shared_ptr <Material>
{
  const MaterialType& type = attributes.MaterialType ();
  if (type == MaterialType::kMatte)
  {
    return CreateMatteMaterial (attributes);
  }
  if (type == MaterialType::kMetal)
  {
    return CreateMetalMaterial (attributes);
  }
  if (type == MaterialType::kPlastic)
  {
    std::cout << "create plastic material" << std::endl;
    return nullptr;
  }
  std::cerr << "Unknown material type detected." << std::endl;
  return nullptr;
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/

