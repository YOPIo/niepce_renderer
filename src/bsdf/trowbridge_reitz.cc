/*!
 * @file trowbridge_reitz_distribution.cc
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#include "trowbridge_reitz.h"
#include "bsdf.h"
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
    Float tan2_theta, phi;
    if (alphax_ == alphay_)
    {
      // Isotropic case
      tan2_theta = alphax_ * alphay_ * sample[0] / (1.0 - sample[0]);
      phi = 2.0 * kPi * sample[1];
    }
    else
    {
      phi = std::atan (alphay_ / alphax_
                      * std::tan (2.0 * kPi * sample[1] + 0.5 * kPi));
      if (sample[1] > 0.5) { phi += kPi; }

      Float sin_phi = std::sin (phi);
      Float cos_phi = std::cos (phi);
      Float alphax2 = alphax_ * alphax_;
      Float alphay2 = alphay_ * alphay_;
      Float alpha2 = 1.0
                   / (cos_phi * cos_phi / alphax2 + sin_phi * sin_phi / alphay2);
      tan2_theta = sample[0] / (1.0 - sample[0]) * alpha2;
    }

    // Compute normal direction from angle.
    Float cos_theta = 1.0 / std::sqrt (1.0 + tan2_theta);
    Float sin_theta = std::sqrt (std::max(0.0, 1.0 - cos_theta * cos_theta));
    auto wm = Vector3f (sin_theta * std::cos (phi),
                        sin_theta * std::sin (phi),
                        cos_theta);

    if (wm.Z () < 0.0) { wm = -wm; }

    return wm;
  }

  std::cerr << "TrowbridgeReits::SampleMicrofacetNormal::Unimplementation" << std::endl;
  // Sample visible area of normals.
  return Vector3f (0, 1, 0);
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
