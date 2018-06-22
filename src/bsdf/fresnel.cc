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
auto FresnelConductor::Evaluate (Float cos_theta1)
  const noexcept -> Float
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

  return 1;
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
  const noexcept -> Float
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

  Float ior1 = outgoing_ior_;
  Float ior2 = incident_ior_;

  // Compute the $ cos(\theta_1) $.
  cos_theta1 = Clamp (cos_theta1,
                      static_cast <Float> (-1.0),
                      static_cast <Float> (1.0));

  // Reflection or refraction
  bool is_entering = cos_theta1 < 0.0;
  if (is_entering)
  {
    // Sampled incident is refraction.
    std::swap (ior1, ior2);
    cos_theta1 = std::fabs (cos_theta1);
  }

  const Float ior = ior1 / ior2;

  // Compute $ cos(\theta_2) $ using Snell's law.
  const Float sin_theta1
    = std::sqrt (std::fmax (0.0, 1 - cos_theta1 * cos_theta1));
  const Float sin_theta2 = ior1 / ior2 * sin_theta1;

  if (sin_theta2 >= 1)
  {
    // Total reflection has occurred.
    return 1.0;
  }

  const Float cos_theta2
    = std::sqrt (std::fmax (0.0, 1.0 - sin_theta2 * sin_theta2));

  // Compute fresnel
  const Float r_parallel
    = (ior * cos_theta1 - cos_theta2) / (ior * cos_theta1 + cos_theta2);
  const Float r_vertical
    = (cos_theta1 - ior * cos_theta2) / (cos_theta1 + ior * cos_theta2);

  return 0.5 * (r_parallel * r_parallel + r_vertical * r_vertical);
}
/*
// ---------------------------------------------------------------------------
*/
} // namespace niepce
