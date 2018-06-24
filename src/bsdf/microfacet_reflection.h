/*!
 * @file microfacet_reflection.h
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#ifndef _MICROFACET_REFLECTION_H_
#define _MICROFACET_REFLECTION_H_
/*
// ---------------------------------------------------------------------------
*/
#include "../core/niepce.h"
#include "beckmann_distribution.h"
#include "bsdf.h"
#include "fresnel.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{

//! ----------------------------------------------------------------------------
//! @class MicrofacetReflection
//! @brief
//! @details
//! ----------------------------------------------------------------------------
class MicrofacetReflection : public Bsdf
{
public:
  //! The default class constructor.
  MicrofacetReflection () = default;

  //! The constructor takes reflectance and roughness.
  MicrofacetReflection
  (
   const Intersection&         intersection,
   const Spectrum&             reflectance,
   const BeckmannDistribution* microfacet,
   const FresnelDielectric*    fresnel
  );

  //! The copy constructor of the class.
  MicrofacetReflection (const MicrofacetReflection& microfacet_reflection)
  = default;

  //! The move constructor of the class.
  MicrofacetReflection (MicrofacetReflection&& microfacet_reflection) = default;

  //! The default class destructor.
  virtual ~MicrofacetReflection () = default;

  //! The copy assignment operator of the class.
  auto operator = (const MicrofacetReflection& microfacet_reflection)
    -> MicrofacetReflection& = default;

  //! The move assignment operator of the class.
  auto operator = (MicrofacetReflection&& microfacet_reflection)
    -> MicrofacetReflection& = default;

public:
  /*!
   * @brief Compute the pdf.
   * @param[in] outgoing
   *    The outgoing direction in BRDF coordinates.
   * @param[in] incident
   *    The incident direction in BRDF coordinates.
   * @return Value of pdf.
   * @exception none
   * @details
   */
  auto Pdf (const BsdfRecord& record)
    const noexcept -> Float override final;

  /*!
   * @brief Evlauate the BSDF
   *
   * @param[in] outgoing
   *    The outgoing direction in the BSDF coordinates.
   * @param[in] incident
   *    The incident direction in the BSDF coordinates.
   *
   * @return The evaluated BSDF.
   *
   * @exception none
   * @details
   */
  auto Evaluate (const BsdfRecord& record)
    const noexcept -> Spectrum override final;

  /*!
   * @brief Sample the BSDF.
   *
   * @param[out] record
   *    Bsdfrecord 
   * @param[in] sample
   *    The uniform distributed sample on [0, 1]^2.
   *
   * @return 
   * @exception none
   * @details
   */
  auto Sample (BsdfRecord* record, const Point2f& sample)
    const noexcept -> Spectrum override final;

private:
  const BeckmannDistribution* microfacet_;
  const FresnelDielectric*    fresnel_;
  const Spectrum              reflectance_;

}; // class MicrofacetReflection
/*
// ---------------------------------------------------------------------------
*/
} // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _MICROFACET_REFLECTION_H_
