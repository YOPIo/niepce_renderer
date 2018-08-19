/*!
 * @file trowbridge_reitz_distribution.cc
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#include "trowbridge_reitz.h"
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
TrowbridgeReitz::TrowbridgeReitz
(
 Float alphax,
 Float alphay,
 bool  sample_visible
) :
  alphax_ (alphax),
  alphay_ (alphay),
  sample_visible_ (sample_visible)
{}
/*
// ---------------------------------------------------------------------------
*/
auto TrowbridgeReitz::Distribution (const Vector3f &w)
  const noexcept -> Float
{
  // Follow Trowbridge Reitz distribution function.
  const Float tan2_theta = bsdf::Tan2Theta (w);
  if (std::isinf (tan2_theta)) { return 0; }
  const Float cos4_theta = bsdf::Cos2Theta (w) * bsdf::Cos2Theta (w);
  const Float e = (bsdf::Cos2Phi (w) / (alphax_ * alphax_)
                +  bsdf::Sin2Phi (w) / (alphay_ * alphay_))
                *  tan2_theta;
  return 1.0 / (kPi * alphax_ * alphay_ * cos4_theta * (1 + e) * (1 + e));
}
/*
// ---------------------------------------------------------------------------
*/
auto TrowbridgeReitz::SampleMicrofacetNormal
(
 const Vector3f &outgoing,
 const Point2f  &sample
)
  const noexcept -> Vector3f
{
  if (!sample_visible_)
  {
    // Sample full distribution of normals.
    Float cos_theta = 0;
    Float phi = 2.0 * kPi * sample[1];
    if (alphax_ == alphay_)
    {
      // Isotropic case
      Float tan2_theta = alphax_ * alphay_ * sample[0] / (1.0 - sample[0]);
      cos_theta = 1.0 / std::sqrt (1 + tan2_theta);
    }
    else
    {
      phi = std::atan (alphay_ / alphax_
                       * std::tan (2.0 * kPi * sample[1] + 0.5 * kPi));
      if (sample[1] > 0.5) { phi += kPi; }
      const Float sin_phi = std::sin (phi);
      const Float cos_phi = std::cos (phi);
      const Float alphax2 = alphax_ * alphax_;
      const Float alphay2 = alphay_ * alphay_;
      const Float alpha2 = 1.0 / (cos_phi * cos_phi / alphax2
                                  + sin_phi * sin_phi / alphay2);
      const Float tan2_theta = alpha2 * sample[0] / (1.0 - sample[0]);
      cos_theta = 1.0 / std::sqrt (1 + tan2_theta);
    }
    const Float sin_theta = std::sqrt (std::fmax (0.0, 1.0 - cos_theta * cos_theta));
    auto half = Vector3f (sin_theta * std::cos (phi),
                          sin_theta * std::sin (phi),
                          cos_theta);
    if (!bsdf::HasSameHemisphere (outgoing, half)) { half = -half; }
    return half;
  }

  std::cerr << "TrowbridgeReits::SampleMicrofacetNormal::Unimplementation" << std::endl;
  // Sample visible area of normals.
  return Vector3f (0, 0, 1);
}
/*
// ---------------------------------------------------------------------------
*/
auto TrowbridgeReitz::GeometricAttenuation
(
 const Vector3f &incident,
 const Vector3f &outgoing
)
  const noexcept -> Float
{
  return 1.0 / (1 + Lambda (incident) + Lambda (outgoing));
}
/*
// ---------------------------------------------------------------------------
*/
auto TrowbridgeReitz::ShadowMasking
(
 const Vector3f &v,
 const Vector3f &half
)
  const noexcept -> Float
{
  return 1.0 / 1.0 + Lambda (v);
}
/*
// ---------------------------------------------------------------------------
*/
auto TrowbridgeReitz::Lambda (const Vector3f &v)
  const noexcept -> Float
{
  const Float abs_tan_theta = std::abs (bsdf::TanTheta (v));
  if (std::isinf (abs_tan_theta)) { return 0; }

  const Float alpha = std::sqrt (bsdf::Cos2Phi (v) * alphax_ * alphax_
                               + bsdf::Sin2Phi (v) * alphay_ * alphay_);
  const Float e = (alpha * abs_tan_theta) * (alpha * abs_tan_theta);
  return (-1 + std::sqrt (1 + e)) * 0.5;
}
/*
// ---------------------------------------------------------------------------
*/
auto TrowbridgeReitz::Pdf
(
 const Vector3f &outgoing,
 const Vector3f &half
)
  const noexcept -> Float
{
  if (!sample_visible_)
  {
    return Distribution (half) * bsdf::AbsCosTheta (half);
  }
  std::cerr << "TrowbridgeReitz::Pdf was called" << std::endl;
  return 1;
}
/*
// ---------------------------------------------------------------------------
*/
auto TrowbridgeReitz::RoughnessToAlpha (Float roughness) -> Float
{
  roughness = std::max (roughness, static_cast <Float> (1e-3));
  const Float x = std::log (roughness);
  return 1.62142f + 0.819955f * x + 0.1734f * x * x + 0.0171201f * x * x * x +
    0.000640711f * x * x * x * x;
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
