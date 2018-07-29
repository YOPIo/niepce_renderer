/*!
 * @file plastic.cc
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#include "plastic.h"
#include "../core/memory.h"
#include "../core/intersection.h"
#include "../core/material_attributes.h"
#include "../bsdf/bsdf.h"
#include "../bsdf/microfacet_reflection.h"
#include "../bsdf/fresnel.h"
#include "../bsdf/trowbridge_reitz.h"
#include "../bsdf/oren_nayar.h"
#include "../bsdf/lambert.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
Plastic::Plastic
(
 const std::shared_ptr <Texture <Spectrum>> &reflectance,
 const std::shared_ptr <Texture <Spectrum>> &specular,
 const std::shared_ptr <Texture <Float>>    &roughness
) :
  Material     (nullptr),
  reflectance_ (reflectance),
  specular_    (specular),
  roughness_   (roughness)
{}
/*
// ---------------------------------------------------------------------------
*/
auto Plastic::AllocateBsdfs
(
 const Intersection &isect,
 MemoryArena *memory
)
  const -> Bsdf* const
{
  // Allocate BSDF.
  Bsdf* const bsdf = memory->Allocate <Bsdf> (isect);

  // Initialize diffuse component of plastic.
  const auto reflectance = reflectance_->Evaluate (isect);
  if (!reflectance.IsBlack ())
  {
    // bsdf->AddBxdf (memory->Allocate <OrenNayar> (reflectance, 15.0));
    // bsdf->AddBxdf (memory->Allocate <Lambert> (reflectance));
  }

  // Initialize specular component of plastic.
  const auto specular = specular_->Evaluate (isect);
  if (!specular.IsBlack ())
  {
    // Generate fresnel.
    const auto f = memory->Allocate <FresnelDielectric> (1.5, 1.0);
    /*
    const auto f = memory->Allocate <FresnelConductor> (Spectrum (1.5),
                                                        Spectrum (1.0),
                                                        Spectrum (specular));
    */
    // Generate microfacet distribution.
    const auto rough
      = TrowbridgeReitz::RoughnessToAlpha (roughness_->Evaluate (isect));
    const auto d = memory->Allocate <TrowbridgeReitz> (rough, rough, false);
    // Generate microfacet reflection.
    bsdf->AddBxdf (memory->Allocate <MicrofacetReflection> (specular, d, f));
  }

  return bsdf;
}
/*
// ---------------------------------------------------------------------------
*/
auto CreatePlasticMaterial (const MaterialAttributes &attrs)
  -> std::shared_ptr <Material>
{
  const auto reflectance
    = attrs.FindSpectrumTextureOrNullPtr (MaterialAttributes::Type::kReflectance);
  const auto specular
    = attrs.FindSpectrumTextureOrNullPtr (MaterialAttributes::Type::kSpecular);
  const auto rough
    = attrs.FindFloatTextureOrNullPtr (MaterialAttributes::Type::kRoughness);

  return std::make_shared <Plastic> (reflectance, specular, rough);
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
