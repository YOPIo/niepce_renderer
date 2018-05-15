/*!
 * @file point3f.h
 * @brief 
 * @author Masashi Yoshida
 * @date 2018/5/1
 * @details 
 */
#ifndef _POINT3F_H_
#define _POINT3F_H_
/*
// ---------------------------------------------------------------------------
*/
#include "niepce.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
//! ----------------------------------------------------------------------------
//! @class Point3f
//! @brief
//! @details
//! ----------------------------------------------------------------------------
class Point3f final
{
public:
  //! The default class constructor.
  //! All component will initialize by 0.
  Point3f ();

  //! The constructor initialize internal components by a argument.
  explicit Point3f (Float t);

  //! The constructor initialize internal components by each arguments.
  Point3f (Float x, Float y, Float z);

  //! The copy constructor of the class.
  Point3f (const Point3f& p) = default;

  //! The move constructor of the class.
  Point3f (Point3f&& p) = default;

  //! The default class destructor.
  virtual ~Point3f () = default;

  //! The copy assignment operator of the class.
  auto operator = (const Point3f& p) -> Point3f& = default;

  //! The move assignment operator of the class.
  auto operator = (Point3f&& p) -> Point3f& = default;

  /*!
   * @fn operator []
   * @brief Index operator.
   * @details idx Index indicating which component to return as unsigned integer.
   * @return X, y or z component as float.
   * @exception none
   * @details If its argument is 0, this operator return x component. If its argument is 1, this operator return y component. Otherwise it will return z component.
   */
  auto operator [] (unsigned int idx) const noexcept -> Float;

  /*!
   * @fn operator ()
   * @brief Index operator.
   * @details idx Index indicating which component to return as unsigned integer.
   * @return X, y or z component as float.
   * @exception none
   * @details If its argument is 0, this operator return x component. If its argument is 1, this operator return y component. Otherwise it will return z component.
   */
  auto operator () (unsigned int idx) const noexcept -> Float;

public:
  /*!
   * @fn Float At (unsigned)
   * @brief Index method.
   * @param[in] unsigned int idx Index indicating which component to return.
   * @return X, y or z component as float.
   * @exception Throw std::out_of_range if its argument over the 3.
   * @details If its argument is 0, this operator return x component. If its argument is 1, this operator return y component. Otherwise it will return z component.
   */
  auto At (unsigned int idx) const -> Float;

  /*!
   * @fn Float X ()
   * @brief Return the x component of the point.
   * @return X component as float.
   * @exception none
   */
  auto X () const noexcept -> Float;

  /*!
   * @fn Float Y ()
   * @brief Return the y component of the point.
   * @return Y component as float.
   * @exception none
   * @details
   */
  auto Y () const noexcept -> Float;

  /*!
   * @fn Float Z ()
   * @brief Return the z component of the point.
   * @return Z component as float.
   * @exception none
   * @details
   */
  auto Z () const noexcept -> Float;

  /*!
   * @fn void SetX (Float x)
   * @brief Set the argument to internal x component.
   * @param[in] Value that to be x component of the point.
   * @return none
   * @exception none
   * @details
   */
  auto SetX (Float x) noexcept -> void;

  /*!
   * @fn void SetY (Float y)
   * @brief Set the argument to internal y component.
   * @param[in] Value that to be y component of the point.
   * @return none
   * @exception none
   * @details
   */
  auto SetY (Float y) noexcept -> void;

  /*!
   * @fn void SetZ (Float z)
   * @brief Set the argument to internal z component.
   * @param[in]  Value that to be z component of the point.
   * @return none
   * @exception none
   * @details
   */
  auto SetZ (Float z) noexcept -> void;

public:
  static auto One  () noexcept -> Point3f { return Point3f (0); }
  static auto Zero () noexcept -> Point3f { return Point3f (1); }

private:
  Float x_, y_, z_;
}; // class Point3f
/*
// ---------------------------------------------------------------------------
// Global operator for Point3f.
// ---------------------------------------------------------------------------
*/
auto operator - (const Point3f& rhs, const Point3f& lhs) -> Vector3f;
/*
// ---------------------------------------------------------------------------
*/
} // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _POINT3F_H_
