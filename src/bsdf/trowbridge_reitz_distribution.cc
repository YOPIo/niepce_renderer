/*!
 * @file trowbridge_reitz_distribution.cc
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#include "trowbridge_reitz_distribution.h"
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
auto TrowbridgeReitzDistribution::Distribution (const Vector3f &half_vector)
  const noexcept -> Float
{
  
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
