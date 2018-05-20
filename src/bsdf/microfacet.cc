/*!
 * @file microfacet.cc
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#include "microfacet.h"
#include "bsdf.h"
#include "../core/point2f.h"
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
 Float roughness,
 Float outgoing_ior,
 Float incident_ior
) :
  Bsdf (intersection),
  reflectance_ (reflectance),
  microfacet_  (BeckmannDistribution (roughness, roughness, false)),
  fresnel_     (FresnelDielectric (outgoing_ior, incident_ior))
{}
/*
// ---------------------------------------------------------------------------
*/
auto MicrofacetReflection::Pdf (const BsdfRecord &record)
  const noexcept -> Float
{
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

  const Float fresnel    = fresnel_.Evaluate (Dot (wh, incident));
  const Float distribute = microfacet_.Distribution (wh);
  const Float gaf        = microfacet_.GeometryAttenuation (outgoing, wh);

  return (reflectance_ * distribute * fresnel)
         / (4.0 * bsdf::AbsCosTheta (outgoing) * bsdf::AbsSinTheta (incident));
}
/*
// ---------------------------------------------------------------------------
*/
auto MicrofacetReflection::Sample
(
 BsdfRecord*    record,
 const Point2f& sample
)
  const noexcept -> Spectrum
{
  const Vector3f outgoing = record->Outgoing ();
  if (outgoing.Z () == 0) { return Spectrum (0); }

  // Sample the microfacet normal and reflected direction (incident direction).
  const Vector3f microfacet_normal
    = microfacet_.SampleMicrofacetNormal (outgoing, sample);
  const Vector3f incident = bsdf::Reflect (outgoing, microfacet_normal);

  record->SetIncident (incident);

  // Error handle
  if (!bsdf::HasSameHemisphere (outgoing, incident)) { return Spectrum (0); }

  // Compute the pdf
  const Float pdf = microfacet_.Pdf (outgoing, microfacet_normal);

  // Evaluate the BSDF
  const Spectrum bsdf = Evaluate (*record);
  return bsdf;
}
/*
// ---------------------------------------------------------------------------
*/
BeckmannDistribution::BeckmannDistribution
(
 Float alpha_x,
 Float alpha_y,
 bool  sample_visible
) :
  alpha_x_ (alpha_x),
  alpha_y_ (alpha_y),
  sample_visible_ (sample_visible)
{}
/*
// ---------------------------------------------------------------------------
*/
auto BeckmannDistribution::Distribution (const Vector3f& m_normal)
  const noexcept -> Float
{
  const Float tan2_theta = bsdf::Tan2Theta (m_normal);

  /* Handle case */
  if (std::isinf (tan2_theta)) { return 0; }

  const Float cos4_theta = bsdf::Cos2theta (m_normal)
                         * bsdf::Cos2theta (m_normal);
  const Float alphax2 = alpha_x_ * alpha_x_;
  const Float alphay2 = alpha_y_ * alpha_y_;
  const Float alphaxy = alpha_x_ * alpha_y_;
  return std::exp (-tan2_theta * (bsdf::Cos2Phi (m_normal) / alphax2) +
                   (bsdf::Sin2Phi (m_normal) / alphay2))
         / (kPi * alphaxy * cos4_theta);

}
/*
// ---------------------------------------------------------------------------
*/
auto BeckmannDistribution::GeometryAttenuation
(
 const Vector3f& outgoing,
 const Vector3f& incident
)
  const noexcept -> Float
{
  return 1.0 / (1.0 + Lambda (outgoing) * Lambda (incident));
}
/*
// ---------------------------------------------------------------------------
*/
auto BeckmannDistribution::Lambda (const Vector3f &w) const noexcept -> Float
{
  const Float cos_theta     = bsdf::CosTheta (w);
  const Float sin_theta     = bsdf::SinTheta (w);
  const Float abs_tan_theta = bsdf::AbsTanTheta (w);

  if (std::isinf (abs_tan_theta)) { return 0.0; }

  const Float alpha = std::sqrt (cos_theta * cos_theta * alpha_x_ * alpha_x_
                                 + sin_theta * sin_theta * alpha_y_ * alpha_y_);
  const Float a = 1.0 / (alpha * abs_tan_theta);
  return (std::erf (a) - 1.0) / 2.0 + std::exp (-a * a)
          / (2.0 * a * std::sqrt (kPi) + 1.0e-6);
}
/*
// ---------------------------------------------------------------------------
*/
auto BeckmannDistribution::Pdf
(
 const Vector3f& outgoing,
 const Vector3f& microfacet_normal
)
  const noexcept -> Float
{
  if (sample_visible_)
  {
    std::cerr << "use FALSE: not implement" << std::endl;
    return 0;
  }
  return Distribution (microfacet_normal) * bsdf::AbsCosTheta (outgoing);
}
/*
// ---------------------------------------------------------------------------
*/
auto BeckmannDistribution::SampleMicrofacetNormal
(
 const Vector3f& outgoing,
 const Point2f&  sample
)
  const noexcept -> Vector3f
{
  if (!sample_visible_)
  {
    // Sample microfacet normal without visibility
    return SampleFullDistribution (outgoing, sample);
  }
  return Vector3f (0, 0, 1);
}
/*
// ---------------------------------------------------------------------------
*/
auto BeckmannDistribution::SampleVisibleOnly (const Vector3f& outgoing)
  const noexcept -> Vector3f
{
  // Todo: implement here
}
/*
// ---------------------------------------------------------------------------
*/
auto BeckmannDistribution::SampleFullDistribution
(
 const Vector3f& outgoing,
 const Point2f&  sample
)
  const noexcept -> Vector3f
{
  if (alpha_x_ == alpha_y_)
  {
    // -------------------------------------------------------------------------
    // This is isotropic case.
    // See the "Microfacet Models for Refraction through Rough Surfaces".
    // Equation (28) and (29).
    // -------------------------------------------------------------------------

    const Float tan2_theta
      = -alpha_x_ * alpha_x_ * std::log (1 - Clamp (sample[0]));
    const Float phi = sample[1] * 2.0 * kPi;

    // Compute microfacet normal.
    const Float cos_theta = 1.0 / std::sqrt (1.0 + tan2_theta);
    const Float sin_theta
      = std::sqrt (std::fmax (0.0, 1.0 - cos_theta * cos_theta));

    Vector3f microfacet_normal = Vector3f (sin_theta * std::cos (phi),
                                           sin_theta * std::sin (phi),
                                           cos_theta);

    if (microfacet_normal.Z () < 0)
    {
      return -microfacet_normal;
    }
    return microfacet_normal;
  }

  // ---------------------------------------------------------------------------
  // Anisotropic case
  // See the "Understanding the Masking-Shadowing Function in Microfacet-Based
  // BRDFs"
  // ---------------------------------------------------------------------------

  const Float y_over_x = alpha_y_ / alpha_x_;
  Float phi = std::atan (y_over_x * std::tan (2.0 * kPi * sample[1] + 0.5 * kPi));
  if (sample[1] > 0.5) { phi += kPi; }

  const Float sin2_phi = std::sin (phi) * std::sin (phi);
  const Float cos2_phi = std::cos (phi) * std::cos (phi);
  const Float alpha_x2 = alpha_x_ * alpha_x_;
  const Float alpha_y2 = alpha_y_ * alpha_y_;

  const Float tan2_theta = -std::log (1.0 - Clamp (sample[0]))
                         / (cos2_phi / alpha_x2 + sin2_phi / alpha_y2);

  // Compute microfacet normal.
  const Float cos_theta = 1.0 / std::sqrt (1.0 + tan2_theta);
  const Float sin_theta
    = std::sqrt (std::fmax (0.0, 1.0 - cos_theta * cos_theta));

  Vector3f microfacet_normal = Vector3f (sin_theta * std::cos (phi),
                                         sin_theta * std::sin (phi),
                                         cos_theta);

  if (microfacet_normal.Z () < 0)
  {
    return -microfacet_normal;
  }
  return microfacet_normal;
}
/*
// ---------------------------------------------------------------------------
*/
} // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
