/*!
 * @file matte.cc
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#include "matte.h"
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
auto Matte::Sample
(
 const Intersection& intersection,
 const Point2f&      sample,
 BsdfRecord*         bsdf_record
)
  const -> void
{
  // Build orthonormal basis.
  const Vector3f normal = intersection.Normal ();
  Vector3f tangent, binormal;
  BuildOrthonormalBasis (normal, &tangent, &binormal);

  // Sample the incident direction.
  const Float r1  = 2.0 * kPi * sample[0];
  const Float r2  = sample[1];
  const Float r2s = std::sqrt (r2);

  const Vector3f incident = tangent * std::cos (r1) * r2s
                          + binormal * std::sin (r1) * r2s
                          + normal * std::sqrt (1.0 - r2);

  // Lambert PDF is constant value $ \cos(theta) / \pi $
  const Float pdf = Dot (incident, normal) / kPi;

  // Calculate BSDF $ reflectance / \pi $
  Vector3f bsdf = reflectance_->Sample (intersection.Texcoord ()) / kPi;

  // Store them
  bsdf_record->SetIncident (incident);
  bsdf_record->SetPdf (pdf);
  bsdf_record->SetBsdfValue (bsdf);
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
