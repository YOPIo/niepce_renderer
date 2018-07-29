/*!
 * @file mirror.cc
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#include "mirror.h"
#include "../bsdf/specular_reflection.h"
#include "../bsdf/fresnel.h"
#include "../bsdf/bsdf.h"
#include "../core/memory.h"
#include "../core/vector3f.h"
#include "../core/material_attributes.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
Mirror::Mirror (const std::shared_ptr <Texture <Spectrum>> &reflectance) :
  Material (nullptr),
  reflectance_(reflectance)
{}
/*
// ---------------------------------------------------------------------------
*/
auto Mirror::AllocateBsdfs
(
 const Intersection &intersection,
 MemoryArena *memory
)
  const -> Bsdf* const
{
  Bsdf* const bsdf = memory->Allocate <Bsdf> (intersection);
  const auto r = reflectance_->Evaluate (intersection);
  /*
  const auto f = memory->Allocate <FresnelConductor> (Spectrum (1.0),
                                                      Spectrum (1.5),
                                                      Spectrum (3.0));
  */
  const auto f = memory->Allocate <FresnelDielectric> (1.0, 1.5);
  bsdf->AddBxdf (memory->Allocate <SpecularReflection> (r, f));

  return bsdf;
}
/*
// ---------------------------------------------------------------------------
*/
auto CreateMirrorMaterial (const MaterialAttributes &attrs)
  -> std::shared_ptr <Material>
{
  const auto r
    = attrs.FindSpectrumTextureOrNullPtr (MaterialAttributes::Type::kReflectance);
  return std::make_shared <Mirror> (r);
}
/*
// ---------------------------------------------------------------------------
*/
} // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
