/*!
 * @file bsdf.h
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#ifndef _BXDF_H_
#define _BXDF_H_
/*
// ---------------------------------------------------------------------------
*/
#include "bxdf_record.h"
#include "../core/niepce.h"
#include "../core/vector3f.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
//! ----------------------------------------------------------------------------
//! @class Bxdf
//! @brief
//! @details
//! ----------------------------------------------------------------------------
class Bxdf
{
public:
  //! The default class constructor.
  Bxdf () = delete;

  //! The constructor takes intersection.
  Bxdf (const Intersection& intersection);

  //! The copy constructor of the class.
  Bxdf (const Bxdf& bsdf) = default;

  //! The move constructor of the class.
  Bxdf (Bxdf&& bsdf) = default;

  //! The default class destructor.
  virtual ~Bxdf () = default;

  //! The copy assignment operator of the class.
  auto operator = (const Bxdf& bsdf) -> Bxdf& = default;

  //! The move assignment operator of the class.
  auto operator = (Bxdf&& bsdf) -> Bxdf& = default;

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
  virtual auto Pdf (const BxdfRecord& record)
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
  virtual auto Evaluate (const BxdfRecord& record)
    const noexcept -> Vector3f = 0;

  /*!
   * @brief Sample the BSDF.
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
  virtual auto Sample (BxdfRecord* record, const Point2f& sample)
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

}; // class Bxdf
/*
// ---------------------------------------------------------------------------
*/
namespace bxdf
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
