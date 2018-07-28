/*!
 * @file distribution_reflection.cc
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#include "microfacet_reflection.h"
#include "bsdf_record.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
MicrofacetReflection::MicrofacetReflection
(
 const Spectrum&        reflectance,
 const TrowbridgeReitz* distribution,
 const Fresnel*         fresnel
) :
  Bxdf (Type (Type::kSpecular | Type::kReflection)),
  reflectance_  (reflectance),
  distribution_ (distribution),
  fresnel_      (fresnel)
{}
/*
// ---------------------------------------------------------------------------
*/
auto MicrofacetReflection::Pdf (const BsdfRecord &record)
  const noexcept -> Float
{
  const auto& outgoing = record.Outgoing (niepce::bsdf::Coordinate::kLocal);
  const auto& incident = record.Incident (niepce::bsdf::Coordinate::kLocal);
  const auto  half     = Normalize (outgoing + incident);

  if (!bsdf::HasSameHemisphere (outgoing, incident))
  {
    // Sampled incident refracted.
    return 0.0;
  }
  const auto pdf = distribution_->Pdf (outgoing, half);
  return distribution_->Pdf (outgoing, half) / (4.0 * Dot (outgoing, half));
}
/*
// ---------------------------------------------------------------------------
*/
auto MicrofacetReflection::Evaluate (const BsdfRecord &record)
  const noexcept -> Spectrum
{
  const auto& outgoing = record.Outgoing (niepce::bsdf::Coordinate::kLocal);
  const auto& incident = record.Incident (niepce::bsdf::Coordinate::kLocal);
  const auto  half     = Normalize (outgoing + incident);

  const auto cto = bsdf::AbsCosTheta (outgoing);
  const auto cti = bsdf::AbsCosTheta (incident);
  /*
  const auto cto = std::fabs (Dot (outgoing, half));
  const auto cti = std::fabs (Dot (incident, half));
  */

  // Handle case
  if (cto == 0 || cti == 0)
  {
    return Spectrum (0);
  }
  if (half.X () == 0 && half.Y () == 0 && half.Z () == 0)
  {
    return Spectrum (0);
  }

  const auto f = fresnel_->Evaluate (std::fabs (Dot (incident, half)));
  const auto d = distribution_->Distribution (half);
  const auto g = distribution_->GeometricAttenuation (outgoing, incident);

  const auto bsdf = reflectance_ * (d * f * g) / (4.0 * cti * cto);

  return bsdf;
}
/*
// ---------------------------------------------------------------------------
*/
auto MicrofacetReflection::Sample
(
 BsdfRecord*    record,
 const Point2f& sample
)
  const noexcept -> Vector3f
{
  // Get outgoing direction in bsdf coordinate.
  const auto outgoing = record->Outgoing (niepce::bsdf::Coordinate::kLocal);

  if (outgoing.Z () == 0) { return Spectrum (0); }

  // Sample the microfacet normal.
  const auto half = distribution_->SampleMicrofacetNormal (outgoing, sample);

  // Compute incident direction in bsdf coordinate system.
  const auto incident = bsdf::Reflect (outgoing, half);
  record->SetIncident (incident, niepce::bsdf::Coordinate::kLocal);

  // Error handle
  if (!bsdf::HasSameHemisphere (outgoing, incident))
  {
    Spectrum (0);
  }

  // Compute the pdf
  const Float pdf = Pdf (*record);
  record->SetPdf (pdf);

  // Evaluate the BSDF
  const Spectrum bsdf = Evaluate (*record);
  record->SetBsdf (bsdf);

  record->SetSampledBsdfType (type_);

  return bsdf;
}
/*
// ---------------------------------------------------------------------------
*/
} // namespace niepce
