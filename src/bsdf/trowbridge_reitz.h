/*!
 * @file trowbridge_reitz_distribution.h
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#ifndef _TROWBRIDGE_REITS_H_
#define _TROWBRIDGE_REITS_H_
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
//! @class TrowbridgeReitz
//! @brief
//! @details
//! ----------------------------------------------------------------------------
class TrowbridgeReitz
{
public:
  //! The default class constructor.
  TrowbridgeReitz () = delete;

  //! The constructor takes alpha x, y and boolean.
  TrowbridgeReitz (Float alphax, Float alphay, bool sample_visible);

  //! The copy constructor of the class.
  TrowbridgeReitz (const TrowbridgeReitz& ggx)
  = default;

  //! The move constructor of the class.
  TrowbridgeReitz (TrowbridgeReitz&& ggx)
  = default;

  //! The default class destructor.
  virtual ~TrowbridgeReitz () = default;

  //! The copy assignment operator of the class.
  auto operator = (const TrowbridgeReitz& ggx)
    -> TrowbridgeReitz& = default;

  //! The move assignment operator of the class.
  auto operator = (TrowbridgeReitz&& ggx)
    -> TrowbridgeReitz& = default;

public:
  /*!
   * @fn Float RoughnessToAlpha (Float)
   * @brief 
   * @param[in] roughness
   *    
   * @return 
   * @exception none
   * @details
   */
  static auto RoughnessToAlpha (Float roughness) -> Float;

public:
  /*!
   * @fn Float Distribution (const Vector3f&)
   * @brief 
   * @param[in] half_vector
   *    
   * @return 
   * @exception none
   * @details
   */
  auto Distribution (const Vector3f &half_vector) const noexcept -> Float;

  /*!
   * @fn Vector3f SampleMicrofacetNormal (const)
   * @brief Sample a microfacet orientation vector.
   * @param[in] outgoing
   *
   * @param[in] sample
   *
   * @return 
   * @exception none
   * @details
   */
  auto SampleMicrofacetNormal (const Vector3f &outgoing, const Point2f &sample)
    const noexcept -> Vector3f;

  /*!
   * @fn Float ShadowMasking (const Vector3f &, const Vector3f &)
   * @brief The shadow masking function gives the fraction of microfacets in a
   *        differential area that are visible from a direction.
   * @param[in] v
   *
   * @param[in] half
   *
   * @return 
   * @exception none
   * @details 
   */
  auto ShadowMasking (const Vector3f &v, const Vector3f &half)
    const noexcept -> Float;

  /*!
   * @fn Float GeometricAttenuation (const Vector3f &, const Vector3f &)
   * @brief The geometric attenuation function gives the fraction of microfacets
   *        in a differential area that are visible from both direction outgoing
   *        and incident.
   * @param[in] incident
   *
   * @param[in] outgoing
   *
   * @return 
   * @exception none
   * @details 
   */
  auto GeometricAttenuation
  (
   const Vector3f &incident,
   const Vector3f &outgoing
  )
  const noexcept -> Float;

  /*!
   * @fn Float Lambda (const)
   * @brief 
   * @param[in] 
   * @param[out] 
   * @return 
   * @exception none
   * @details 
   */
  auto Lambda (const Vector3f &v) const noexcept -> Float;

  /*!
   * @fn Float Pdf (const)
   * @brief 
   * @param[in] outgoing
   *     
   * @param[in] incident
   *     
   * @return 
   * @exception none
   * @details
   */
  auto Pdf (const Vector3f &outgoing, const Vector3f &half)
    const noexcept -> Float;

private:
  const Float alphax_, alphay_;
  const bool  sample_visible_;

}; // class TrowbridgeReitz
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _TROWBRIDGE_REITS_H_
