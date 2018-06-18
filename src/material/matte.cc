/*!
 * @file matte.cc
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#include "matte.h"
#include "../core/texture_attributes.h"
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
 const std::shared_ptr <Texture>& reflectance,
 const std::shared_ptr <Texture>& emission
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
  const Spectrum reflectance = reflectance_->Sample (intersection.Texcoord ());

  Bsdf* const bsdf_ptr = memory->Allocate <Lambert> (intersection, reflectance);

  return bsdf_ptr;
}
/*
// ---------------------------------------------------------------------------
*/
auto CreateMatteMaterial (const TextureAttributes& attributes) -> Material*
{
  const std::shared_ptr <Texture> emission
    = attributes.FindTexture ("emission");
  const std::shared_ptr <Texture> reflectance
    = attributes.FindTexture ("reflectance");
  return new Matte (emission, reflectance);
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
