/*!
 * @file lambert.h
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#ifndef _LAMBERT_H_
#define _LAMBERT_H_
/*
// ---------------------------------------------------------------------------
*/
#include "bxdf.h"
#include "bxdf_record.h"
#include "../sampler/sampler.h"
#include "../core/vector3f.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
//! ----------------------------------------------------------------------------
//! @class Lambert
//! @brief
//! @details
//! ----------------------------------------------------------------------------
class Lambert : public Bxdf
{
public:
  //! The default class constructor.
  Lambert () = default;

  //! The copy constructor of the class.
  Lambert (const Lambert& lambert) = default;

  //! The move constructor of the class.
  Lambert (Lambert&& lambert) = default;

  //! The default class destructor.
  virtual ~Lambert () = default;

  //! The copy assignment operator of the class.
  auto operator = (const Lambert& lambert) -> Lambert& = default;

  //! The move assignment operator of the class.
  auto operator = (Lambert&& lambert) -> Lambert& = default;

public:
  /*!
   * @fn Float Pdf (const)
   * @brief Compute the pdf.
   * @param[in] outgoing
   *    The outgoing direction in BRDF coordinates.
   * @param[in] incident
   *    The incident direction in BRDF coordinates.
   * @return Value of pdf.
   * @exception none
   * @details
   */
  auto Pdf (const BxdfRecord& record)
    const noexcept -> Float override final;

  /*!
   * @fn Return Function (Param)
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
  auto Evaluate (const BxdfRecord& record)
    const noexcept -> Vector3f override final;

  /*!
   * @fn Return Sample (BxdfRecord*)
   * @brief 
   * @param[in] 
   * @param[out] record
   *    
   * @return 
   * @exception none
   * @details
   */
  auto Sample (BxdfRecord* record, const Point2f& sample)
    const noexcept -> Vector3f override final;

}; // class Lambert
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _LAMBERT_H_
