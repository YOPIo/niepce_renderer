/*!
 * @file trowbridge_reitz_distribution.h
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#ifndef _TROWBRIDGE_REITS_DISTRIBUTION_H_
#define _TROWBRIDGE_REITS_DISTRIBUTION_H_
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
//! @class TrowbridgeReitzDistribution
//! @brief
//! @details
//! ----------------------------------------------------------------------------
class TrowbridgeReitzDistribution
{
public:
  //! The default class constructor.
  TrowbridgeReitzDistribution () = delete;

  //! The constructor takes alpha x, y and boolean.
  TrowbridgeReitzDistribution (Float alphax, Float alphay, bool sample_visible);

  //! The copy constructor of the class.
  TrowbridgeReitzDistribution (const TrowbridgeReitzDistribution& ggx)
  = default;

  //! The move constructor of the class.
  TrowbridgeReitzDistribution (TrowbridgeReitzDistribution&& ggx)
  = default;

  //! The default class destructor.
  virtual ~TrowbridgeReitzDistribution () = default;

  //! The copy assignment operator of the class.
  auto operator = (const TrowbridgeReitzDistribution& ggx)
    -> TrowbridgeReitzDistribution& = default;

  //! The move assignment operator of the class.
  auto operator = (TrowbridgeReitzDistribution&& ggx)
    -> TrowbridgeReitzDistribution& = default;

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

private:
  Float alphax_, alphay_;
  bool  sample_visible_;

}; // class TrowbridgeReitzDistribution
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _TROWBRIDGE_REITS_DISTRIBUTION_H_
