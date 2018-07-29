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
FresnelDielectric::FresnelDielectric (Float outgoing_ior, Float incident_ior) :
  outgoing_ior_ (outgoing_ior),
  incident_ior_ (incident_ior)
{}
/*
// ---------------------------------------------------------------------------
*/
auto FresnelDielectric::Evaluate (Float cos_theta1)
  const noexcept -> Spectrum
{
  /*!
                    normal
                       |    /
                       |   /
                       |  / outgoing
                       |-/
                       |/ \theta_1     index of refraction 1 (ior_o)
             ---------------------
             \theta_2 /|               index of refraction 2 (ior_i)
                     /-|
                    /  |
                   /   |
                  /    |
          incident  -normal

    Snell's law
    $ n_1 * sin(\theta_1) = n_2 * sin(\theta_2) $
   */

  auto ior1 = outgoing_ior_;
  auto ior2 = incident_ior_;

  // Compute the $ cos(\theta_1) $.
  cos_theta1 = Clamp (cos_theta1,
                      static_cast <Float> (-1.0),
                      static_cast <Float> (1.0));

  // Reflection or refraction
  bool is_entering = cos_theta1 > 0.0;
  if (!is_entering)
  {
    // Sampled incident is refraction.
    std::swap (ior1, ior2);
    cos_theta1 = std::fabs (cos_theta1);
  }

  // Compute $ cos(\theta_2) $ using Snell's law.
  const auto sin_theta1 = std::sqrt (std::fmax (0.0, 1.0 - cos_theta1 * cos_theta1));
  const auto sin_theta2 = ior2 / ior1 * sin_theta1;

  if (sin_theta2 >= 1)
  {
    // Total reflection has occurred.
    return Spectrum (1.0);
  }

  const auto cos_theta2
    = std::sqrt (std::fmax (0.0, 1.0 - sin_theta2 * sin_theta2));

  // Compute fresnel
  const auto r_parallel = ((ior2 * cos_theta1) - (ior1 * cos_theta2))
                        / ((ior2 * cos_theta1) + (ior1 * cos_theta2));
  const auto r_vertical = ((ior1 * cos_theta1) - (ior2 * cos_theta2))
                        / ((ior1 * cos_theta1) + (ior2 * cos_theta2));

  auto f = Spectrum ((r_parallel * r_parallel + r_vertical * r_vertical) * 0.5);
  return f;
}
/*
// ---------------------------------------------------------------------------
*/
} // namespace niepce
