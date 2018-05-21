/*!
 * @file microfacet_reflection.cc
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
 const Intersection& intersection,
 const Spectrum& reflectance,
 const BeckmannDistribution* microfacet,
 const FresnelDielectric* fresnel
) :
  Bsdf (intersection),
  reflectance_ (reflectance),
  microfacet_  (microfacet),
  fresnel_     (fresnel)
{}
/*
// ---------------------------------------------------------------------------
*/
auto MicrofacetReflection::Pdf (const BsdfRecord &record)
  const noexcept -> Float
{
  const Vector3f& outgoing = record.Outgoing ();
  const Vector3f& incident = record.Incident ();

  if (!bsdf::HasSameHemisphere (outgoing, incident))
  {
    // Sampled incident refracted.
    return 0.0;
  }

  return microfacet_->Pdf (outgoing, incident) / (4.0 * Dot (outgoing, incident));
}
/*
// ---------------------------------------------------------------------------
*/
auto MicrofacetReflection::Evaluate (const BsdfRecord &record)
  const noexcept -> Spectrum
{
  const Vector3f& outgoing = record.Outgoing ();
  const Vector3f& incident = record.Incident ();
  const Vector3f wh = (outgoing + incident).Normalize ();

  const Float outgoing_cos_theta = bsdf::AbsCosTheta (outgoing);
  const Float incident_cos_theta = bsdf::AbsCosTheta (incident);

  // Handle case
  if (outgoing_cos_theta == 0 || incident_cos_theta == 0)
  {
    return Spectrum (0);
  }
  if (wh.X () == 0 && wh.Y () == 0 && wh.Z () == 0)
  {
    return Spectrum (0);
  }

  const Float fresnel    = fresnel_->Evaluate (Dot (wh, incident));
  const Float distribute = microfacet_->Distribution (wh);
  const Float gaf        = microfacet_->GeometryAttenuation (outgoing, wh);

  const Spectrum bsdf =(reflectance_ * distribute * fresnel)
    / (4.0 * bsdf::AbsCosTheta (outgoing) * bsdf::AbsSinTheta (incident));

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
  const Vector3f outgoing = record->Outgoing ();

  // Sample the microfacet normal and reflected direction (incident direction).
  const Vector3f microfacet_normal
    = microfacet_->SampleMicrofacetNormal (outgoing, sample);
  const Vector3f incident = bsdf::Reflect (outgoing, microfacet_normal);

  record->SetIncident (incident);

  // Error handle
  if (!bsdf::HasSameHemisphere (outgoing, incident)) { return Spectrum (0); }

  // Compute the pdf
  const Float pdf = microfacet_->Pdf (outgoing, microfacet_normal);
  record->SetPdf (pdf);

  // Evaluate the BSDF
  const Spectrum bsdf = Evaluate (*record);
  record->SetBsdf (bsdf);

  // Compute $ cos(\theta) $
  const Float cos_t = Dot (microfacet_normal, incident);

  return this->ToWorld (incident);
}
/*
// ---------------------------------------------------------------------------
*/
} // namespace niepce
