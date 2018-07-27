/*!
 * @file matte.cc
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#include "matte.h"
#include "../core/material_attributes.h"
#include "../core/attributes.h"
#include "../core/intersection.h"
#include "../core/memory.h"
#include "../bsdf/lambert.h"
#include "../bsdf/oren_nayar.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
Matte::Matte
(
 const std::shared_ptr <Texture <Spectrum>>& emission,
 const std::shared_ptr <Texture <Spectrum>>& reflectance
) :
  Material     (emission),
  reflectance_ (reflectance)
{}
/*
// ---------------------------------------------------------------------------
*/
auto Matte::AllocateBsdfs
(
 const Intersection& intersection,
       MemoryArena*  memory
)
const -> Bsdf* const
{
  Bsdf* const bsdf = memory->Allocate <Bsdf> (intersection);

  const auto reflectance = reflectance_->Evaluate (intersection);
  bsdf->AddBxdf (memory->Allocate <Lambert> (reflectance));
  bsdf->AddBxdf (memory->Allocate <OrenNayar> (reflectance, 20));

  return bsdf;
}
/*
// ---------------------------------------------------------------------------
*/
auto CreateMatteMaterial (const MaterialAttributes& attributes)
  -> std::shared_ptr <Material>
{
  const auto emission
    = attributes.FindSpectrumTextureOrNullPtr (MaterialAttributes::Type::kEmission);
  const auto reflectance
    = attributes.FindSpectrumTextureOrNullPtr (MaterialAttributes::Type::kReflectance);

  return std::make_shared <Matte> (emission, reflectance);
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
