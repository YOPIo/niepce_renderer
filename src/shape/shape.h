/*!
 * @file shape.h
 * @brief 
 * @author Masashi Yoshida
 * @date 2018/5/5
 * @details 
 */
#ifndef _SHAPE_H_
#define _SHAPE_H_
/*
// ---------------------------------------------------------------------------
*/
#include "../core/niepce.h"
#include "../core/ray.h"
#include "../core/intersection.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
//! ----------------------------------------------------------------------------
//! @class Shape
//! @brief The fundamental class, all shape class should inherit this class.
//! @details
//! ----------------------------------------------------------------------------
class Shape
{
public:
  //! The default class constructor.
  Shape () = default;

  //! The copy constructor of the class.
  Shape (const Shape& shape) = default;

  //! The move constructor of the class.
  Shape (Shape&& shape) = default;

  //! The default class destructor.
  virtual ~Shape () = default;

  //! The copy assignment operator of the class.
  auto operator = (const Shape& shape) -> Shape& = default;

  //! The move assignment operator of the class.
  auto operator = (Shape&& shape) -> Shape& = default;

public:
  /*!
   * @fn void Intersect (const Ray& ray, Intersection* intersection)
   * @brief 
   * @param[in] ray 
   * @param[out] intersection Ray intersected with a shape or not.
   * @return void
   * @exception none
   * @details
   */
  virtual auto IsIntersect
  (
   const Ray& ray,
   Intersection* intersection
  )
  const noexcept -> bool = 0;

protected:
  const Float kIntersectionEpsilon = 1e-4;
}; // class Shape
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _SHAPE_H_
