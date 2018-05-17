/*!
 * @file bsdf.h
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#ifndef _BSDF_H_
#define _BSDF_H_
/*
// ---------------------------------------------------------------------------
*/
#include "bsdf_record.h"
#include "../core/niepce.h"
#include "../core/vector3f.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
//! ----------------------------------------------------------------------------
//! @class Bsdf
//! @brief
//! @details
//! ----------------------------------------------------------------------------
class Bsdf
{
public:
  //! The default class constructor.
  Bsdf () = default;

  //! The copy constructor of the class.
  Bsdf (const Bsdf& bsdf) = default;

  //! The move constructor of the class.
  Bsdf (Bsdf&& bsdf) = default;

  //! The default class destructor.
  virtual ~Bsdf () = default;

  //! The copy assignment operator of the class.
  auto operator = (const Bsdf& bsdf) -> Bsdf& = default;

  //! The move assignment operator of the class.
  auto operator = (Bsdf&& bsdf) -> Bsdf& = default;

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
  virtual auto Pdf (const BsdfRecord& record)
    const noexcept -> Float = 0;

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
  virtual auto Evaluate (const BsdfRecord& record)
    const noexcept -> Vector3f = 0;

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
  virtual auto Sample (BsdfRecord* record, const Point2f& sample)
    const noexcept -> Vector3f = 0;


protected:
  /*!
   * @brief
   *    The normal vector at the intersection in world coordinates.
   */
  const Vector3f normal_;

  /*!
   * @brief
   *    The tangent vector at the intersection in world coordinates.
   *    It will be computed at the constructor automatically.
   */
  Vector3f tangent_;

  /*!
   * @brief
   *    The binormal vector at the intersection in world coordinates.
   *    It will be computed at the constructor automatically.
   */
  Vector3f binormal_;

}; // class Bsdf
/*
// ---------------------------------------------------------------------------
*/
namespace bsdf
{
/*
// ---------------------------------------------------------------------------
*/
auto Dot   (const Vector3f& v) -> Float;
auto Cross (const Vector3f& v) -> Vector3f;
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _BSDF_H_
