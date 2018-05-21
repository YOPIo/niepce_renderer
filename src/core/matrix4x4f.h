/*!
 * @file matrix4x4.h
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#ifndef _MATRIX4X4F_H_
#define _MATRIX4X4F_H_
/*
// ---------------------------------------------------------------------------
*/
#include "niepce.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
//! ----------------------------------------------------------------------------
//! @class Matrix4x4f
//! @brief
//! @details
//! ----------------------------------------------------------------------------
class Matrix4x4f
{
public:
  //! The default class constructor.
  Matrix4x4f ();

  //! The constructor takes each components.
  Matrix4x4f (Float m00, Float m01, Float m02, Float m03,
              Float m10, Float m11, Float m12, Float m13,
              Float m20, Float m21, Float m22, Float m23,
              Float m30, Float m31, Float m32, Float m33);

  //! The copy constructor of the class.
  Matrix4x4f (const Matrix4x4f& mat) = default;

  //! The move constructor of the class.
  Matrix4x4f (Matrix4x4f&& mat) = default;

  //! The default class destructor.
  virtual ~Matrix4x4f () = default;

  //! The copy assignment operator of the class.
  auto operator = (const Matrix4x4f& mat) -> Matrix4x4f& = default;

  //! The move assignment operator of the class.
  auto operator = (Matrix4x4f&& mat) -> Matrix4x4f& = default;

public:
  /*!
   * @fn operator ()
   * @brief 
   * @param[in] x
   *    Index of row.
   * @param[in] y
   *    Index of column.
   * @details 
   * @return 
   * @exception none
   */
  auto operator () (unsigned int x, unsigned int y) const noexcept -> Float;

public:
  //! @fn Float At (unsigned)
  //! @brief 
  //! @param[in] x
  //!    Index of row.
  //! @param[in] y
  //!    Index of column.
  //! @return 
  //! @exception none
  //! @details 
  auto At (unsigned int x, unsigned int y) const -> Float;

  /*!
   * @fn void SetFloat (Float)
   * @brief 
   * @param[in] value
   *    
   * @return 
   * @exception none
   * @details 
  */
  auto SetFloat (unsigned int x, unsigned int y, Float value) -> void;

  /*!
   * Return
   *        1 0 0 0
   *        0 1 0 0
   *        0 0 1 0
   *        0 0 0 1
   */
  static auto Identity () -> Matrix4x4f;

private:
  std::array <std::array <Float, 4>, 4> m_;

}; // class Matrix4x4f
/*
// ---------------------------------------------------------------------------
// Matrix4x4f operators
// ---------------------------------------------------------------------------
*/
auto operator == (const Matrix4x4f& lhs, const Matrix4x4f& rhs) -> bool;
auto operator != (const Matrix4x4f& lhs, const Matrix4x4f& rhs) -> bool;

auto operator * (const Matrix4x4f& lhs, const Matrix4x4f& rhs) -> Matrix4x4f;
/*
// ---------------------------------------------------------------------------
// Matrix4x4f functions
// ---------------------------------------------------------------------------
*/
auto Transpose (const Matrix4x4f& m) -> Matrix4x4f;
auto Inverse   (const Matrix4x4f& m) -> Matrix4x4f;
/*
// ---------------------------------------------------------------------------
*/
} // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _MATRIX4X4_H_

