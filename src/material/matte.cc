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
 const std::shared_ptr <Texture>& emission,
 const std::shared_ptr <Texture>& reflectance
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
  const auto reflectance = reflectance_->Sample (intersection.Texcoord ());
  auto const bsdf_ptr = memory->Allocate <Lambert> (intersection, reflectance);

  return bsdf_ptr;
}
/*
// ---------------------------------------------------------------------------
*/
auto CreateMatteMaterial (const MaterialAttributes& attributes)
  -> std::shared_ptr <Material>
{
  const auto emission    = attributes.FindTexture (TextureType::kEmission);
  const auto reflectance = attributes.FindTexture (TextureType::kReflectance);

  return std::make_shared <Matte> (emission, reflectance);
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
