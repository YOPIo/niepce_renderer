/*!
 * @file microfacet.h
 * @brief 
 * @author Masashi Yoshdia
 * @date 
 * @details 
 */
#ifndef _MICROFACET_H_
#define _MICROFACET_H_
/*
// ---------------------------------------------------------------------------
*/
#include "bsdf.h"
#include "fresnel.h"
#include "../core/niepce.h"
#include "../core/vector3f.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
//! ----------------------------------------------------------------------------
//! @class BeckmannDistribution
//! @brief
//! @details
//! ----------------------------------------------------------------------------
class BeckmannDistribution
{
public:
  //! The default class constructor.
  BeckmannDistribution () = delete;

  //! The constructor takes alphas and boolean.
  BeckmannDistribution (Float alpha_x, Float alpha_y, bool sample_visible);

  //! The copy constructor of the class.
  BeckmannDistribution (const BeckmannDistribution& beckmann) = default;

  //! The move constructor of the class.
  BeckmannDistribution (BeckmannDistribution&& beckmann) = default;

  //! The default class destructor.
  virtual ~BeckmannDistribution () = default;

  //! The copy assignment operator of the class.
  auto operator = (const BeckmannDistribution& beckmann)
    -> BeckmannDistribution& = default;

  //! The move assignment operator of the class.
  auto operator = (BeckmannDistribution&& beckmann)
    -> BeckmannDistribution& = default;

public:
  /*!
   * @fn Float Distribution (const)
   * @brief Evalute beckmann distribution equation.
   *
   * @param[in] microfacet_normal
   *    The sampled microsurface normal direction.
   * @return 
   *
   * @exception none
   * @details
   */
  auto Distribution (const Vector3f& microfacet_normal) const noexcept -> Float;

  //! @fn Float GeometryAttenuation (const Vector3f&, const Vector3f&)
  //! @brief 
  //! @param[in] outgoing
  //!    
  //! @param[in] microfacet_normal
  //!    
  //! @return 
  //! @exception none
  //! @details 
  auto GeometryAttenuation
  (
   const Vector3f& outgoing,
   const Vector3f& microfacet_normal
  )
  const noexcept -> Float;

  //! @fn Float; Lambda (const Vector3f&)
  //! @brief 
  //! @param[in] w
  //!    
  //! @return 
  //! @exception none
  //! @details 
  auto Lambda (const Vector3f& w) const noexcept -> Float;


  /*! @fn Vector3f SampleMicrofacetNormal (const Vector3f)
   * @brief Sample the microfacet normal.
   *
   * @param[in] outgoing
   *    The outgoing direction in BSDF coordinates.
   *
   * @return Microfacet normal vector.
   * @exception none
   * @details 
   */
  auto SampleMicrofacetNormal
  (
   const Vector3f& outgoing,
   const Point2f&  sample
  )
  const noexcept -> Vector3f;

  /*!
   * @fn Float Pdf (const Vector3f&, const Vector3f&)
   * @brief Compute the pdf.
   *
   * @param[in] outgoing
   *    The outgoing direction.
   * @param[in] incident
   *    The incident direction.
   *
   * @return Pdf
   * @exception none
   * @details
   */
  auto Pdf
  (
   const Vector3f& outgoing,
   const Vector3f& incident
  )
  const noexcept -> Float;

private:
  /*! @fn Vector3f SampleVisibleonly (const Vector3f&)
   * @brief Sample the microfacet normal.
   *
   * @param[in] outgoing
   *    The outgoing direction in BSDF coordinates.
   *
   * @return Microfacet normal vector.
   * @exception none
   * @details 
   */
  auto SampleVisibleOnly (const Vector3f& outgoing) const noexcept -> Vector3f;

  /*! @fn Vector3f SampleWithoutvisibility (const Vector3f&)
   * @brief Sample the microfacet normal.
   *
   * @param[in] outgoing
   *    The outgoing direction in BSDF coordinates.
   *
   * @return tangent^2 theta and phi
   * @exception none
   * @details 
   */
  auto SampleFullDistribution
  (
   const Vector3f& outgoing,
   const Point2f&  sample
  )
  const noexcept -> Vector3f;

private:
  Float alpha_x_;
  Float alpha_y_;
  bool  sample_visible_;
}; // class BeckmannDistribution
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
   const Intersection& intersection,
   const Spectrum& reflectance,
   Float roughness,
   Float outgoing_ior,
   Float incident_ior
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
  const BeckmannDistribution microfacet_;
  const FresnelDielectric    fresnel_;
  const Spectrum reflectance_;

}; // class MicrofacetReflection
/*
// ---------------------------------------------------------------------------
*/
} // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _MICROFACET_H_
