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
#include "bsdf.h"
#include "bsdf_record.h"
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
class Lambert : public Bsdf
{
public:
  //! The default class constructor.
  Lambert () = delete;

  //! The constructor takes reflectance.
  Lambert (const Spectrum& reflectance);

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
  auto Pdf (const BsdfRecord& record)
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
  auto Evaluate (const BsdfRecord& record)
    const noexcept -> Spectrum override final;

  /*!
   * @fn Return Sample (BsdfRecord*)
   * @brief 
   * @param[in] 
   * @param[out] record
   *    
   * @return 
   * @exception none
   * @details
   */
  auto Sample (BsdfRecord* record, const Point2f& sample)
    const noexcept -> Spectrum override final;

private:
  const Spectrum reflectance_;
}; // class Lambert
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _LAMBERT_H_
