/*!
 * @file distribution_reflection.cc
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#include "microfacet_reflection.h"
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
 const Intersection&    intersection,
 const Spectrum&        reflectance,
 const TrowbridgeReitz* distribution,
 const Fresnel*         fresnel
) :
  Bsdf (BsdfType::kSpecular, intersection),
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
  const auto& outgoing = record.Outgoing ();
  const auto& incident = record.Incident ();
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
  const Vector3f& outgoing = record.Outgoing ();
  const Vector3f& incident = record.Incident ();
  const Vector3f  half = Normalize (outgoing + incident);

  const Float cto = bsdf::AbsCosTheta (outgoing);
  const Float cti = bsdf::AbsCosTheta (incident);

  // Handle case
  if (cto == 0 || cti == 0)
  {
    return Spectrum (0);
  }
  if (half.X () == 0 && half.Y () == 0 && half.Z () == 0)
  {
    return Spectrum (0);
  }

  const auto f = fresnel_->Evaluate (Dot (incident, half));
  const auto d = distribution_->Distribution (half);
  const auto g = distribution_->GeometricAttenuation (outgoing, incident);

  const Spectrum bsdf = reflectance_ * (d * f * g) / (4.0 * cti * cto);

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
  const auto outgoing = record->Outgoing ();
  if (outgoing.Z () == 0) { return Spectrum (0); }

  // Sample the microfacet normal.
  const auto half = distribution_->SampleMicrofacetNormal (outgoing, sample);

  // Compute incident direction in bsdf coordinate system.
  const auto incident = bsdf::Reflect (outgoing, half);
  record->SetIncident (incident);

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

  // Compute $ cos(\theta) $
  const Float cos_t = std::fabs (Dot (normal_, incident));
  record->SetCosTheta (cos_t);

  return ToWorld (incident);
}
/*
// ---------------------------------------------------------------------------
*/
} // namespace niepce
