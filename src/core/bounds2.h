/*!
 * @file rectangle.h
 * @brief 
 * @author Masashi Yoshida
 * @date 2018/4/18
 * @details 
 */
#ifndef _BOUNDS2_H_
#define _BOUNDS2_H_
/*
// ---------------------------------------------------------------------------
*/
#include "niepce.h"
#include "vector2f.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
//! ----------------------------------------------------------------------------
//! @class Bounds2
//! @brief 
//! @details 
//! ----------------------------------------------------------------------------
template <typename T>
class Bounds2
{
public:
  //! The default class constructor.
  /*!
   * You need to initialize min and max by constructor
   */
  Bounds2 () = delete;

  //! Constructor
  /*!
   * Initialize min [first_x, first_y] and max [last_x, last_y]
   */
  Bounds2 (T first_x, T first_y, T last_x, T last_y);

  //! The copy constructor of the class.
  Bounds2 (const Bounds2& rect) = default;

  //! The move constructor of the class.
  Bounds2 (Bounds2&& rect) = default;

  //! The default class destructor.
  virtual ~Bounds2 () = default;

  //! The copy assignment operator of the class.
  auto operator = (const Bounds2& rect) -> Bounds2& = default;

  //! The move assignment operator of the class.
  auto operator = (Bounds2&& rect) -> Bounds2& = default;

  //! @fn std::pair <T, T> Min ()
  //! @brief 
  //! @details 
  //! @return 2D coordinate point
  //! @exception none
  auto Min () const -> Vector2f;

  //! @fn std::pair <T, T> Max ()
  //! @brief 
  //! @return 2D coordinate point
  //! @exception none
  //! @details 
  auto Max () const -> Vector2f;

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
  // TODO: Replace Vector2f to Point2f
  Vector2f min_, max_;

}; // class Bounds2
/*
// ---------------------------------------------------------------------------
*/
} // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _BOUNDS2_H_

