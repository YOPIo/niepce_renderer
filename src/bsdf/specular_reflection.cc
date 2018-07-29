/*!
 * @file specular_reflection.cc
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#include "specular_reflection.h"
#include "bsdf_record.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
SpecularReflection::SpecularReflection
(
 const Spectrum &reflectance,
 Fresnel        *fresnel
) :
  Bxdf (Bxdf::Type (Bxdf::Type::kReflection | Bxdf::Type::kSpecular)),
  reflectance_ (reflectance),
  fresnel_     (fresnel)
{}
/*
// ---------------------------------------------------------------------------
*/
auto SpecularReflection::Pdf (const BsdfRecord &record) const noexcept -> Float
{
  // !
  return 1.0;
}
/*
// ---------------------------------------------------------------------------
*/
auto SpecularReflection::Evaluate (const BsdfRecord &record)
  const noexcept -> Spectrum
{
  const auto &wi = record.Incident (bsdf::Coordinate::kLocal);
  return fresnel_->Evaluate (bsdf::CosTheta (wi)) * reflectance_
         / bsdf::AbsCosTheta (wi);
}
/*
// ---------------------------------------------------------------------------
*/
auto SpecularReflection::Sample(BsdfRecord *record, const Point2f &sample)
  const noexcept -> Spectrum
{
  // Compute perfect specular reflection direction.
  const auto wi = bsdf::Reflect (record->Outgoing (bsdf::Coordinate::kLocal),
                                 Vector3f (0, 0, 1));
  record->SetIncident (wi, bsdf::Coordinate::kLocal);

  // Pdf is always 1.
  // const auto pdf = Pdf (*record);
  record->SetPdf (1.0);

  const auto f = Evaluate (*record);
  record->SetBsdf (f);

  return f;
}
/*
// ---------------------------------------------------------------------------
*/
} // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
