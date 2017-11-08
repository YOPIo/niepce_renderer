#include "matte.h"
#include "../bxdf/lambert.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
Matte::Matte (const std::shared_ptr<Texture<Spectrum>>& reflectance) :
  reflectance_ (reflectance)
{}
/*
// ---------------------------------------------------------------------------
*/
auto Matte::AllocateBsdf
(
 const SurfaceInteraction& si,
       ArenaAllocator*     mem
)
const -> Bsdf*
{
  // Generate BSDF
  Bsdf*    bsdf = mem->Allocate<Bsdf> (si);

  // Create lambertian BRDF
  Spectrum reflectance (reflectance_->Evaluate (si));
  Bxdf*    lambert = mem->Allocate<Lambert> (reflectance);
  bsdf->Push (lambert);

  return bsdf;
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
