/*!
 * @file fresnel.cc
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#include "bsdf.h"
#include "fresnel.h"
#include "../core/vector3f.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
FresnelConductor::FresnelConductor
(
 const Spectrum &ior_i,
 const Spectrum &ior_t,
 const Spectrum &absorption
) :
  ior_incident_ (ior_i),
  ior_transmit_ (ior_t),
  absorption_   (absorption)
{}
/*
// ---------------------------------------------------------------------------
*/
auto FresnelConductor::Evaluate (Float cos_theta_i)
  const noexcept -> Spectrum
{
  // Follow just fresnel equation.

  // Compute cos(\theta_i)
  cos_theta_i = Clamp (cos_theta_i, -1.f, 1.f);

  const auto ior    = ior_transmit_ / ior_incident_;
  const auto absorp = absorption_ / ior_incident_;

  // cos^(2)(\theta_i)
  const Float cti2 = cos_theta_i * cos_theta_i;
  // sin^(2)(\theta_i)
  const Float sti2 = 1.0 - cti2;

  const auto ior2    = ior * ior;
  const auto absorp2 = absorp * absorp;

  const auto ab       = ior2 - absorp2 - Spectrum (sti2); // ???
  const auto a2plugb2 = Sqrt (ab * ab + 4.0 * ior2 * absorp2);
  const auto a        = Sqrt (0.5f * (a2plugb2 + ab));
  const auto t1       = a2plugb2 + Spectrum (cti2);
  const auto t2       = 2.0 * cos_theta_i * a;
  const auto vertical = (t1 - t2) / (t1 + t2);

  const auto t3       = cti2 * a2plugb2 + Spectrum (sti2) * Spectrum (sti2);
  const auto t4       = t2 * sti2;
  const auto parallel = vertical * (t3 - t4) / (t3 + t4);

  return 0.5 * (vertical + parallel);
}
/*
// ---------------------------------------------------------------------------
*/
FresnelDielectric::FresnelDielectric (Float i, Float t) :
  ior_i_ (i),
  ior_t_ (t)
{}
/*
// ---------------------------------------------------------------------------
*/
auto FresnelDielectric::Evaluate (Float cos_t1)
  const noexcept -> Spectrum
{
  cos_t1 = Clamp (cos_t1, -1.0f, 1.0f);
  auto ior_i = ior_i_;
  auto ior_t = ior_t_;
  if (cos_t1 > 0) { std::swap (ior_i, ior_t); }

  const auto sin_t2 = ior_i / ior_t
                    * std::sqrt (std::fmax (0.0, 1.0 - cos_t1 * cos_t1));
  if (sin_t2 >= 1.0)
  {
    // Total reflection.
    return Spectrum (1);
  }
  const auto cos_t2 = std::sqrt (std::fmax (0.0, 1.0 - sin_t2 * sin_t2));
  cos_t1 = std::fabs (cos_t1);

  const auto rs = ((ior_t * cos_t1) - (ior_i * cos_t2))
                / ((ior_t * cos_t1) + (ior_i * cos_t2));
  const auto rp = ((ior_i * cos_t1) - (ior_t * cos_t2))
                / ((ior_i * cos_t1) + (ior_t * cos_t2));
  const auto kr = (rs * rs + rp * rp) * 0.5;
  return Spectrum (kr);

  /*
  const Float n = cos_t1 > 0 ? ior_i_ / ior_t_ : ior_t_ / ior_i_;

  const Float cos2_t2 = 1.0 - n * n * (1.0 - cos_t1 * cos_t1);
  if (cos2_t2 < 0)
  {
    // Total reflection.
    return Spectrum (1.0);
  }

  const Float cos_t2 = std::sqrt (cos2_t2);
  const Float r_parallel = (n * cos_t1 - cos_t2) / (n * cos_t1 + cos_t2);
  const Float r_vertical = (cos_t1 - n * cos_t2) / (cos_t1 + n * cos_t2);

  const Float f = 0.5 * (r_parallel * r_parallel + r_vertical * r_vertical);
  return Spectrum (f);
  */
}
/*
// ---------------------------------------------------------------------------
*/
} // namespace niepce
