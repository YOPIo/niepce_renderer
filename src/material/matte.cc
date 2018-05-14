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
  // Sample the incident direction.
    const Float r1  = 2.0 * kPi * sample[0];
    const Float r2  = sample[1];
    const Float r2s = std::sqrt (r2);

    const Float tx = r2s * std::cos (r1);
    const Float ty = r2s * std::sin (r1);
    const Float tz = std::sqrt (1 - r2);

    const Vector3f normal = intersection.Normal ();

    Vector3f tangent, binormal;
    BuildOrthonormalBasis (normal, &tangent, &binormal);

    const Vector3f incident = normal * tz + tangent * tx + binormal * ty;

    // Lambert PDF is constant value $ \cos(theta) / \pi $
    const Float pdf = Dot (incident, normal);

    // Calculate BSDF
    Vector3f bsdf = reflectance_->Sample (intersection.Texcoord ());

    // Store them
    bsdf_record->SetIncident (incident);
    bsdf_record->SetPdf (pdf);
    bsdf_record->SetBsdfValue (bsdf);
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
