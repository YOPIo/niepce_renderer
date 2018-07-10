/*!
 * @file oren_nayar.h
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#include "oren_nayar.h"
#include "bsdf_record.h"
#include "../sampler/sampler.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
OrenNayar::OrenNayar (const Spectrum &reflectance, Float degree) :
  Bxdf (Type (Type::kReflection | Type::kDiffuse)),
  reflectance_ (reflectance),
  radians_     (ToRadian (degree)),
  a_ (1.0 - (radians_ * radians_) / (2.0 * (radians_ * radians_ + 0.33))),
  b_ ((0.45 * radians_ * radians_) / (radians_ * radians_ + 0.09))
{}
/*
// ---------------------------------------------------------------------------
*/
auto OrenNayar::Pdf (const BsdfRecord &record) const noexcept -> Float
{
  const Vector3f incident = record.Incident (niepce::bsdf::Coordinate::kLocal);
  //! Lambert PDF : $ cos\theta / \pi $
  const Float pdf = std::fabs (bsdf::CosTheta (incident) / kPi);
  return pdf;
}
/*
// ---------------------------------------------------------------------------
*/
auto OrenNayar::Evaluate (const BsdfRecord &record) const noexcept -> Spectrum
{
  // Get the outgoing and incident direction in BSDF space.
  const auto &wo = record.Outgoing (bsdf::Coordinate::kLocal);
  const auto &wi = record.Incident (bsdf::Coordinate::kLocal);

  Float sin_theta_i = bsdf::SinTheta (wi);
  Float sin_theta_o = bsdf::SinTheta (wo);

  // Compute $ cos(phi_i - phi_o) $ term.
  Float cos = 0;
  if (sin_theta_i > 1e-4 && sin_theta_o > 1e-4)
  {
    auto cos_phi_i = bsdf::CosPhi (wi);
    auto cos_phi_o = bsdf::CosPhi (wo);
    auto sin_phi_i = bsdf::SinPhi (wi);
    auto sin_phi_o = bsdf::SinPhi (wo);
    cos = std::fmax (0.0, cos_phi_i * cos_phi_o +sin_phi_i * sin_phi_o);
  }

  // Compute $ sin(\alpha) $ and $ tan(\beta) $ term.
  Float sin, tan;
  if (bsdf::AbsCosTheta (wi) > bsdf::AbsCosTheta (wo))
  {
    sin = sin_theta_o;
    tan = sin_theta_i / bsdf::AbsCosTheta (wi);
  }
  else
  {
    sin = sin_theta_i;
    tan = sin_theta_o / bsdf::AbsCosTheta (wo);
  }
  return reflectance_ * (a_ + b_ * cos * sin * tan) / kPi;
}
/*
// ---------------------------------------------------------------------------
*/
auto OrenNayar::Sample (BsdfRecord *record, const Point2f &sample)
  const noexcept -> Spectrum
{
  // Sample the incident direction in BSDF space.
  const auto wi = SampleCosineHemisphere (sample);
  record->SetIncident (wi, niepce::bsdf::Coordinate::kLocal);

  const auto pdf = Pdf (*record);
  record->SetPdf (pdf);

  const auto bsdf = Evaluate (*record);
  record->SetBsdf (bsdf);

  return bsdf;
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
