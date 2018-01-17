#include "matte.h"
#include "../bxdf/lambert.h"
#include "../bxdf/oren_layar.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
Matte::Matte (const Vector3f& reflectance)
{
  const TexturePtr<Spectrum> texture
      = CreateConstantTexture (Vector4f (reflectance.r,
                                         reflectance.g,
                                         reflectance.b,
                                         1.0));
  reflectance_ = texture;
}
/*
// ---------------------------------------------------------------------------
*/
Matte::Matte (const Vector4f& reflectance) :
    reflectance_ (CreateConstantTexture (reflectance))
{}
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
  Bsdf* bsdf = mem->Allocate <Bsdf> (si);

  // Create lambertian BRDF
  Spectrum reflectance (reflectance_->Evaluate (si));
  // Bxdf* lambert    = mem->Allocate <Lambert> (reflectance);
  // bsdf->Push (lambert);
  Bxdf* oren_layar = mem->Allocate <OrenLayar> (reflectance, 0.3);
  bsdf->Push (oren_layar);


  return bsdf;
}
/*
// ---------------------------------------------------------------------------
*/
auto CreateMatte (const TexturePtr <Spectrum>& reflectance) -> MaterialPtr
{
  return std::make_shared <Matte> (reflectance);
}
/*
// ---------------------------------------------------------------------------
*/
auto CreateMatte (const Vector3f& reflectance) -> MaterialPtr
{
  return std::make_shared <Matte> (reflectance);
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
