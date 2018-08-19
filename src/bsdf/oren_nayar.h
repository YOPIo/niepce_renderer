/*!
 * @file oren_nayar.h
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#ifndef _OREN_NAYAR_H_
#define _OREN_NAYAR_H_
/*
// ---------------------------------------------------------------------------
*/
#include "bxdf.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
//! ----------------------------------------------------------------------------
//! @class OrenNayar
//! @brief
//! @details
//! ----------------------------------------------------------------------------
class OrenNayar : public Bxdf
{
public:
  //! The default class constructor.
  OrenNayar () = delete;

  //! The constructor takes reflectance and degree.
  OrenNayar (const Spectrum &reflectance, Float degree);

  //! The copy constructor of the class.
  OrenNayar (const OrenNayar& oren_nayar) = default;

  //! The move constructor of the class.
  OrenNayar (OrenNayar&& oren_nayar) = default;

  //! The default class destructor.
  virtual ~OrenNayar () = default;

  //! The copy assignment operator of the class.
  auto operator = (const OrenNayar& oren_nayar) -> OrenNayar& = default;

  //! The move assignment operator of the class.
  auto operator = (OrenNayar&& oren_nayar) -> OrenNayar& = default;

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
   * @brief Evlauate the BXDF
   *
   * @param[in] outgoing
   *    The outgoing direction in the BXDF coordinates.
   * @param[in] incident
   *    The incident direction in the BXDF coordinates.
   *
   * @return The evaluated BXDF.
   *
   * @exception none
   * @details
   */
  auto Evaluate (const BsdfRecord& record)
    const noexcept -> Spectrum override final;

  /*!
   * @brief Sample the BXDF.
   *
   * @param[out] record
   *    Bxdfrecord 
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
  const Spectrum reflectance_;
  const Float    radians_;
  const Float    a_;
  const Float    b_;

}; // class OrenNayar
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _OREN_NAYAR_H_
