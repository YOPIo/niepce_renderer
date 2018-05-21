/*!
 * @file metal.cc
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#include "metal.h"
#include "../bsdf/beckmann_distribution.h"
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
 const std::shared_ptr <Texture>& reflectance,
 const std::shared_ptr <Texture>& roughness_u,
 const std::shared_ptr <Texture>& roughness_v,
 const std::shared_ptr <Texture>& ior,
 const std::shared_ptr <Texture>& emission
) :
  Material (emission),
  reflectance_ (reflectance),
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
  const Point2f uv = intersection.Texcoord ();

  // Allocate distribution model
  const Float roughness_u = RgbToMonochrome (roughness_u_->Sample (uv));
  const Float roughness_v = RgbToMonochrome (roughness_v_->Sample (uv));
  BeckmannDistribution* distribution
    = memory->Allocate <BeckmannDistribution> (roughness_u,
                                               roughness_v,
                                               false);
  // Allocate fresnel model
  const Float ior = RgbToMonochrome (ior_->Sample (uv));
  FresnelDielectric* fresnel = memory->Allocate <FresnelDielectric> (1.0, ior);

  // Allocate microfacet BRDF
  Bsdf* const metal
    = memory->Allocate <MicrofacetReflection> (intersection,
                                               reflectance_->Sample(uv),
                                               distribution,
                                               fresnel);
  return metal;
}
/*
// ---------------------------------------------------------------------------
*/
} // namespace niepce
