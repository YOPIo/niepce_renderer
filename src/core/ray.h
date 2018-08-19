/*!
 * @file ray.h
 * @brief 
 * @author Masashi Yoshida
 * @date 2018/4/30
 * @details 
 */
#ifndef _RAY_H_
#define _RAY_H_
/*
// ---------------------------------------------------------------------------
*/
#include "niepce.h"
#include "point3f.h"
#include "vector3f.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
//! ----------------------------------------------------------------------------
//! @class Ray
//! @brief
//! @details
//! ----------------------------------------------------------------------------
class Ray
{
public:
  //! The default class constructor.
  Ray () = default;

  //! The constructor takes origin and direction.
  Ray (const Point3f& o, const Vector3f& d);

  //! The copy constructor of the class.
  Ray (const Ray& ray);

  //! The move constructor of the class.
  Ray (Ray&& ray);

  //! The default class destructor.
  virtual ~Ray () = default;

  //! The copy assignment operator of the class.
  auto operator = (const Ray& ray) -> Ray&;

  //! The move assignment operator of the class.
  auto operator = (Ray&& ray) -> Ray&;

  /*!
   * @fn Vector3f Direction ()
   * @brief Return the direction of ray.
   * @return Direction of ray as Vector3f.
   * @exception none
   * @details
   */
  auto Direction () const noexcept -> Vector3f;

  /*!
   * @fn Vector3f Origin ()
   * @brief Return the position of ray origin.
   * @return Position indicating ray origin as Point3f.
   * @exception none
   * @details
   */
  auto Origin () const noexcept -> Point3f;

  /*!
   * @fn Point3f IntersectAt (Float)
   * @brief Compute the intersection position of this ray.
   * @param[in] t The distance as Float.
   * @return The intersection position in world coordinate.
   * @exception none
   * @details
   */
  auto IntersectAt (Float t) const noexcept -> Point3f;

  /*!
   * @fn std ToString ()
   * @brief 
   * @return 
   * @exception none
   * @details
   */
  auto ToString () const noexcept -> std::string;

private:
  Point3f  origin_;
  Vector3f direction_;
}; // class Ray
/*
// ---------------------------------------------------------------------------
*/
auto operator == (const Ray &lhs, const Ray &rhs) -> bool;
/*
// ---------------------------------------------------------------------------
*/
} // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _RAY_H_
