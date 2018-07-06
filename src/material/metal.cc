/*!
 * @file metal.cc
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#include "metal.h"
#include "../core/attributes.h"
#include "../core/material_attributes.h"
#include "../bsdf/beckmann_distribution.h"
#include "../bsdf/trowbridge_reitz_distribution.h"
#include "../bsdf/fresnel.h"
#include "../bsdf/microfacet_reflection.h"
#include "../core/memory.h"
#include "../core/intersection.h"
#include "../core/utilities.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
Metal::Metal
(
 const std::shared_ptr <Texture>& absorption,
 const std::shared_ptr <Texture>& roughness_u,
 const std::shared_ptr <Texture>& roughness_v,
 const std::shared_ptr <Texture>& ior
) :
  Material (nullptr),
  absorption_  (absorption),
  roughness_u_ (roughness_u),
  roughness_v_ (roughness_v),
  ior_ (ior)
{}
/*
// ---------------------------------------------------------------------------
*/
auto Metal::AllocateBsdfs
(
 const Intersection& intersection,
       MemoryArena*  memory
)
const -> Bsdf* const
{
  return nullptr;
}
/*
// ---------------------------------------------------------------------------
*/
auto CreateMetalMaterial (const MaterialAttributes& attrs)
  -> std::shared_ptr <Material>
{
  const auto absorption = attrs.FindTexture (TextureType::kAbsorption);
  const auto roughness_u = attrs.FindTexture (TextureType::kRoughnessU);
  const auto roughness_v = attrs.FindTexture (TextureType::kRoughnessV);

  return nullptr;
}
/*
// ---------------------------------------------------------------------------
*/
} // namespace niepce
