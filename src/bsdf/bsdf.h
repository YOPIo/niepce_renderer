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
  Bsdf () = delete;

  //! Tha constructor takes intersection.
  Bsdf (const Intersection& intersection);

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
  /*! @fn Vector3f ToLocal (const Vector3f&)
   * @brief Transform vector in world coordiantes to BSDF coordiantes.
   * @param[in] w
   *    The vector in world coordinates.
   * @return Vector in BSDF coordinates.
   * @exception none
   * @details 
   */
  auto ToLocal (const Vector3f& w) const noexcept -> Vector3f;

  /*! @fn Vector3f ToWorld (const Vector3f&)
   * @brief Transform vector in BSDF coordiantes to world coordinates.
   * @param[in] w
   *    The vector in BSDF coordinates.
   * @return 
   * @exception none
   * @details 
  */
  auto ToWorld (const Vector3f& w) const noexcept -> Vector3f;

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
auto CosTheta    (const Vector3f& w) -> Float;
auto Cos2Theta   (const Vector3f& w) -> Float;
auto AbsCosTheta (const Vector3f& w) -> Float;

auto SinTheta    (const Vector3f& w) -> Float;
auto Sin2Theta   (const Vector3f& w) -> Float;
auto AbsSinTheta (const Vector3f& w) -> Float;

auto TanTheta    (const Vector3f& w) -> Float;
auto Tan2Theta   (const Vector3f& w) -> Float;
auto AbsTanTheta (const Vector3f& w) -> Float;
/*
// ---------------------------------------------------------------------------
*/
auto CosPhi    (const Vector3f& w) -> Float;
auto Cos2Phi   (const Vector3f& w) -> Float;
auto AbsCosPhi (const Vector3f& w) -> Float;

auto SinPhi    (const Vector3f& w) -> Float;
auto Sin2Phi   (const Vector3f& w) -> Float;
auto AbsSinPhi (const Vector3f& w) -> Float;

auto TanPhi    (const Vector3f& w) -> Float;
auto Tan2Phi   (const Vector3f& w) -> Float;
auto AbsTanPhi (const Vector3f& w) -> Float;
/*
// ---------------------------------------------------------------------------
*/
auto Dot   (const Vector3f& v) -> Float;
auto Cross (const Vector3f& v) -> Vector3f;
auto HasSameHemisphere (const Vector3f& lhs, const Vector3f& rhs) -> bool;
auto Reflect (const Vector3f& vector, const Vector3f& normal) -> Vector3f;
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
