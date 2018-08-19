/*!
 * @file beckmann_distribution.h
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#ifndef _BECKMANN_DISTRIBUTION_H_
#define _BECKMANN_DISTRIBUTION_H_
/*
// ---------------------------------------------------------------------------
*/
#include "../core/niepce.h"
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
/*
// ---------------------------------------------------------------------------
*/
} // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _BECKMANN_DISTRIBUTION_H_
