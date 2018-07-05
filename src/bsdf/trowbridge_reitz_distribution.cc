/*!
 * @file trowbridge_reitz_distribution.cc
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#include "trowbridge_reitz_distribution.h"
#include "bsdf.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
TrowbridgeReitzDistribution::TrowbridgeReitzDistribution
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
auto TrowbridgeReitzDistribution::Distribution (const Vector3f &w)
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
auto TrowbridgeReitzDistribution::GeometricAttenuation
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
auto TrowbridgeReitzDistribution::ShadowMasking
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
auto TrowbridgeReitzDistribution::Lambda (const Vector3f &v)
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
auto TrowbridgeReitzDistribution::RoughnessToAlpha (Float roughness) -> Float
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
