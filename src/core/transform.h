/*!
 * @file transform.h
 * @brief 
 * @author Masashi Yoshdia
 * @date 
 * @details 
 */
#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_
/*
// ---------------------------------------------------------------------------
*/
#include "niepce.h"
#include "matrix4x4f.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
//! ----------------------------------------------------------------------------
//! @class Transform
//! @brief
//! @details
//! ----------------------------------------------------------------------------
class Transform
{
public:
  //! The default class constructor.
  Transform () = default;

  //! The constructor takes matrix.
  Transform (const Matrix4x4f& mat);

  //! The constructor takes matrix components.
  Transform (Float m00, Float m01, Float m02, Float m03,
             Float m10, Float m11, Float m12, Float m13,
             Float m20, Float m21, Float m22, Float m23,
             Float m30, Float m31, Float m32, Float m33);

  Transform (const Matrix4x4f& mat, const Matrix4x4f& inv);

  //! The copy constructor of the class.
  Transform (const Transform& t) = default;

  //! The move constructor of the class.
  Transform (Transform&& t) = default;

  //! The default class destructor.
  virtual ~Transform () = default;

  //! The copy assignment operator of the class.
  auto operator = (const Transform& t) -> Transform& = default;

  //! The move assignment operator of the class.
  auto operator = (Transform&& t) -> Transform& = default;

  /*!
   * @fn operator (unsigned int, unsigned int)
   * @brief 
   * @details 
   * @return 
   * @exception none
   */
  auto operator () (unsigned int x, unsigned int y) const noexcept -> Float;

public:
  /*!
   * @fn Float At (unsigned)
   * @brief 
   * @param[in] x
   *    unsigned integer.
   * @param[in] y
   *    unsigned integer.
   * @return 
   * @exception none
   * @details
   */
  auto At (unsigned int x, unsigned int y) const noexcept -> Float;

  /*!
   * @fn Matrix4x4f Matrix () const noexcept
   * @brief 
   * @return 
   * @exception none
   * @details
   */
  auto Matrix () const noexcept -> Matrix4x4f;

  /*!
   * @fn Matrix4x4f InverseMatrix () const noexcept
   * @brief 
   * @return 
   * @exception none
   * @details
   */
  auto InverseMatrix () const noexcept -> Matrix4x4f;

  /*!
   * @fn std ToString ()
   * @brief 
   * @return 
   * @exception none
   * @details
   */
  auto ToString () const noexcept -> std::string;

private:
  Matrix4x4f mat_;
  Matrix4x4f inv_;
}; // class Transform
/*
// ---------------------------------------------------------------------------
// Transform operators
// ---------------------------------------------------------------------------
*/
auto operator == (const Transform& lhs, const Transform& rhs) -> bool;
auto operator != (const Transform& lhs, const Transform& rhs) -> bool;
/*
// ---------------------------------------------------------------------------
*/
auto operator * (const Transform& t, Float s) -> Transform;
auto operator * (Float s, const Transform& t) -> Transform;
/*
// ---------------------------------------------------------------------------
*/
auto operator * (const Transform& t1, const Transform& t2) -> Transform;
auto operator * (const Transform& t,  const Point3f&  p) -> Point3f;
auto operator * (const Transform& t,  const Vector3f& v) -> Vector3f;
auto operator * (const Transform& t,  const Ray&      r) -> Ray;
/*
// ---------------------------------------------------------------------------
// Transform functions
// ---------------------------------------------------------------------------
*/
auto Transpose (const Transform& t) -> Transform;
auto Inverse   (const Transform& t) -> Transform;
auto LookAt
(
 const Point3f&  position,
 const Point3f&  look,
 const Vector3f& up
)
  -> Transform;
auto Perspective (Float fov, Float near, Float far) -> Transform;
/*
// ---------------------------------------------------------------------------
*/
auto Scale (Float x, Float y, Float z) -> Transform;
auto Translate (const Vector3f& delta) -> Transform;
auto RotateX (Float theta) -> Transform;
auto RotateY (Float theta) -> Transform;
auto RotateZ (Float theta) -> Transform;
/*
// ---------------------------------------------------------------------------
*/
} // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _TRANSFORM_H_

