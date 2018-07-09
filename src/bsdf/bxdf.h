/*!
 * @file bxdf.h
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
  enum Type
  {
    kDiffuse      = 1 << 1,
    kSpecular     = 1 << 2,
    kGlossy       = 1 << 3,
    kReflection   = 1 << 4,
    kTransmittion = 1 << 5,
    kUnknown      = 1 << 0,
    kAll          = kDiffuse
                  | kSpecular
                  | kGlossy
                  | kReflection
                  | kTransmittion,
  };

public:
  //! The default class constructor.
  Bxdf () = default;

  //! Tha constructor takes intersection.
  Bxdf (niepce::Bxdf::Type type);

  //! The copy constructor of the class.
  Bxdf (const Bxdf& bxdf) = default;

  //! The move constructor of the class.
  Bxdf (Bxdf&& bxdf) = default;

  //! The default class destructor.
  virtual ~Bxdf () = default;

  //! The copy assignment operator of the class.
  auto operator = (const Bxdf& bxdf) -> Bxdf& = default;

  //! The move assignment operator of the class.
  auto operator = (Bxdf&& bxdf) -> Bxdf& = default;

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
  virtual auto Pdf (const BsdfRecord& record)
    const noexcept -> Float = 0;

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
  virtual auto Evaluate (const BsdfRecord& record)
    const noexcept -> Spectrum = 0;

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
  virtual auto Sample (BsdfRecord* record, const Point2f& sample)
    const noexcept -> Spectrum = 0;

  /*!
   * @fn BsdfType Type ()
   * @brief 
   * @return 
   * @exception none
   * @details
   */
  auto BsdfType () const noexcept -> niepce::Bxdf::Type;

  /*!
   * @fn bool FulFill (niepce)
   * @brief 
   * @param[in] type
   * @return 
   * @exception none
   * @details
   */
  auto FulFill (niepce::Bxdf::Type type) const noexcept -> bool;

protected:
  /*!
   * @brief
   *    The type of BXDF.
   */
  Type type_;
}; // class Bxdf
/*
// ---------------------------------------------------------------------------
*/
namespace bsdf
{
/*
// ---------------------------------------------------------------------------
*/
enum class Coordinate : uint8_t
{
  kWorld,
  kLocal
};
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
auto Refract
(
 const Vector3f& vector,
 const Vector3f& normal,
 Float ior1,
 Float ior2,
 Vector3f* refract
)
  -> bool;
/*
// ---------------------------------------------------------------------------
*/
}  // namespace bsdf
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _BXDF_H_
