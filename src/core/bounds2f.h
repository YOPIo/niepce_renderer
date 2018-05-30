/*!
 * @file bounds2f.h
 * @brief 
 * @author Masashi Yoshida
 * @date 2018/5/5
 * @details 
 */
#ifndef _BOUNDS2F_H_
#define _BOUNDS2F_H_
/*
// ---------------------------------------------------------------------------
*/
#include "niepce.h"
#include "point2f.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
//! ----------------------------------------------------------------------------
//! @class Bounds2f
//! @brief
//! @details
//! ----------------------------------------------------------------------------
class Bounds2f
{
public:
  //! The default class constructor.
  Bounds2f ();

  //! The constructor takes two points.
  Bounds2f (const Point2f& p0, const Point2f& p1);

  //! The copy constructor of the class.
  Bounds2f (const Bounds2f& bounds) = default;

  //! The move constructor of the class.
  Bounds2f (Bounds2f&& bounds) = default;

  //! The default class destructor.
  virtual ~Bounds2f () = default;

  //! The copy assignment operator of the class.
  auto operator = (const Bounds2f& bounds) -> Bounds2f& = default;

  //! The move assignment operator of the class.
  auto operator = (Bounds2f&& bounds) -> Bounds2f& = default;

public:
  /*!
   * @fn Point2f Max ()
   * @brief Return the maximum point of bounds.
   * @return Position of maximum as Point2f.
   * @exception none
   * @details
   */
  auto Max () const noexcept -> Point2f;

  /*!
   * @fn Point2f Min ()
   * @brief Return the minimum point of bounds.
   * @return Position of minimum as Point2f.
   * @exception none
   * @details
   */
  auto Min () const noexcept -> Point2f;

  /*!
   * @fn void SetMax (const Point2f& max)
   * @brief Set the argument to internal data as maximum point.
   * @param[in] max Maximum point.
   * @return void
   * @exception none
   * @details
   */
  auto SetMax (const Point2f& max) noexcept -> void;

  /*!
   * @fn void SetMin (const Point2f& min)
   * @brief Set the argument to internal data as minimum point.
   * @param[in] min Minimum point.
   * @return void
   * @exception none
   * @details
   */
  auto SetMin (const Point2f& min) noexcept -> void;

  /*!
   * @fn std ToString ()
   * @brief 
   * @return 
   * @exception none
   * @details
   */
  auto ToString () const noexcept -> std::string;

  /*!
   * @fn bool IsInside (const Point2f&)
   * @brief 
   * @param[in] p
   *    2-dimensional point
   * @return Return true if point inside of bounding box, otherwise return false.
   * @exception none
   * @details
   */
  auto IsInside (const Point2f& p) const noexcept -> bool;

public:
  Point2f min_, max_;
}; // class Bounds2f
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _BOUNDS2F_H_
