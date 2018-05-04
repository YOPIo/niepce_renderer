/*!
 * @file point2.h
 * @brief 
 * @author Masashi Yoshida
 * @date 2018/4/29
 * @details 
 */
#ifndef _POINT2_H_
#define _POINT2_H_
/*
// ---------------------------------------------------------------------------
*/
#include "../core/niepce.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
//! ----------------------------------------------------------------------------
//! @class Point2f
//! @brief
//! @details
//! ----------------------------------------------------------------------------
class Point2f final
{
public:
  //! The default class constructor.
  Point2f () = default;

  //! The constructor initialize all internal component by a argument.
  explicit Point2f (Float t);

  //! The constructor initialize internal component by arguments.
  Point2f (Float x, Float y);

  //! The copy constructor of the class.
  Point2f (const Point2f& p) = default;

  //! The move constructor of the class.
  Point2f (Point2f&& p) = default;

  //! The default class destructor.
  virtual ~Point2f () = default;

  //! The copy assignment operator of the class.
  auto operator = (const Point2f& p) -> Point2f& = default;

  //! The move assignment operator of the class.
  auto operator = (Point2f&& p) -> Point2f& = default;

  /*!
   * @fn operator [unsigned int]
   * @brief Index operator
   * @param idx Index indicating which component to return as unsigned integer.
   * @return X, or y component as float.
   * @exception none
   * @details If its argument is 0, this operator return x component. Otherwise it will return y component.
   */
  auto operator [] (unsigned int idx) const noexcept -> Float;

  /*!
   * @fn operator (unsigned int)
   * @brief Index operator
   * @param idx Index indicating which component to return as unsigned integer.
   * @return X, or y component as float.
   * @exception none
   * @details If its argument is 0, this operator return x component. Otherwise it will return y component.
   */
  auto operator () (unsigned int) const noexcept -> Float;

public:
  /*!
   * @fn Float At (unsigned int idx)
   * @brief Index operator
   * @param idx Index indicating which component to return as unsigned integer.
   * @return X, or y component as float.
   * @exception Throw std::out_of_range if its argument over the 2.
   * @details If its argument is 0, this operator return x component. Otherwise it will return y component.
   */
  auto At (unsigned int idx) const -> Float;

  //! @fn Float X ()
  //! @brief Return x component of the point.
  //! @return X component as float.
  //! @exception none
  auto X () const noexcept -> Float;

  //! @fn Float Y ()
  //! @brief Return y component.
  //! @return The component of y of the point.
  //! @exception none
  auto Y () const noexcept -> Float;

  //! @fn void SetX ()
  //! @brief Set the argument to the x component of the point
  //! @param[in] Value that to be x component of the point.
  //! @return none
  //! @exception none
  auto SetX (Float x) noexcept -> void;

  //! @fn void SetX ()
  //! @brief Set the argument to the y component of the point
  //! @param[in] Value that to be y component of the point.
  //! @return none
  //! @exception none
  auto SetY (Float y) noexcept -> void;

private:
  Float x_, y_;
}; // class Point2f
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#include "point2f.inl"
/*
// ---------------------------------------------------------------------------
*/
#endif // _POINT2_H_
