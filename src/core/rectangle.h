/*!
 * @file rectangle.h
 * @brief 
 * @author Masashi Yoshida
 * @date 2018/4/18
 * @details 
 */
#ifndef _RECTANGLE_H_
#define _RECTANGLE_H_
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
//! @class Rectangle
//! @brief 
//! @details 
//! ----------------------------------------------------------------------------
template <typename T>
class Rectangle
{
public:
  //! Default constructor
  /*!
   * You need to initialize min and max by constructor
   */
  Rectangle () = delete;

  //! Constructor
  /*!
   * Initialize min and max
   */
  Rectangle (T begin_x, T begin_y, T end_x,   T end_y);

  //! Copy constructor
  Rectangle (const Rectangle& rect) = default;

  //! Move constructor
  Rectangle (Rectangle&& rect) = default;

  //! Destructor
  virtual ~Rectangle () = default;

  //! Copy assignment operator
  auto operator = (const Rectangle& rect) -> Rectangle& = default;

  //! Move assignment operator
  auto operator = (Rectangle&& rect) -> Rectangle& = default;

  //! @fn std::pair <T, T> GetMin ()
  //! @brief 
  //! @details 
  //! @return 2D coordinate point
  //! @exception none
  auto GetMin () const -> std::pair <T, T>;

  //! @fn std::pair <T, T> GetMax ()
  //! @brief 
  //! @return 2D coordinate point
  //! @exception none
  //! @details 
  auto GetMax () const -> std::pair <T, T>;

  //! @fn Return SetMin (T x, T y)
  //! @brief Set min component
  //! @param[in] x component
  //! @param[in] y component
  //! @return void
  //! @exception none
  //! @details 
  auto SetMin (T x, T y) -> void;

  //! @fn void SetMax (T x, T y)
  //! @brief Set min component
  //! @param[in] x component
  //! @param[in] y component
  //! @return void
  //! @exception none
  //! @details 
  auto SetMax (T x, T y) -> void;

private:
  std::pair <T, T> min_, max_;
}; // class Rectangle
/*
// ---------------------------------------------------------------------------
*/
} // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _RECTANGLE_H_

