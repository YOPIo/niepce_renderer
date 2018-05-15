/*!
 * @file matte.cc
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#include "matte.h"
#include "material_parameters.h"
#include "../bsdf/bsdf_record.h"
#include "../texture/value_texture.h"
#include "../texture/image_texture.h"
#include "../core/pixel.h"
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
auto Matte::AllocateBsdf 
(
 const Intersection& intersection,
       MemoryArena*  memory
)
const -> Bsdf*
{
  
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
