/*!
 * @file bounds3f.h
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#ifndef _BOUNDS3F_H_
#define _BOUNDS3F_H_
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
//! @class Bounds3f
//! @brief
//! @details
//! ----------------------------------------------------------------------------
class Bounds3f
{
public:
  //! The default class constructor.
  Bounds3f () = default;

  //! The constructor takes pair of poionts.
  Bounds3f (const Point3f& p1, const Point3f& p2);

  //! The copy constructor of the class.
  Bounds3f (const Bounds3f& bounds3) = default;

  //! The move constructor of the class.
  Bounds3f (Bounds3f&& bounds3) = default;

  //! The default class destructor.
  virtual ~Bounds3f () = default;

  //! The copy assignment operator of the class.
  auto operator = (const Bounds3f& bounds3) -> Bounds3f& = default;

  //! The move assignment operator of the class.
  auto operator = (Bounds3f&& bounds3) -> Bounds3f& = default;

public:
  /*!
   * @fn Point3f Min ()
   * @brief Return the minimum point.
   * @return 
   * @exception none
   * @details 
  */
  auto Center () const noexcept -> Point3f;

  /*!
   * @fn Point3f Min ()
   * @brief Return the minimum point.
   * @return 
   * @exception none
   * @details 
  */
  auto Diagonal () const noexcept -> Vector3f;

  /*!
   * @fn Point3f Min ()
   * @brief Return the minimum point.
   * @return 
   * @exception none
   * @details 
  */
  auto Min () const noexcept -> Point3f;

  /*!
   * @fn Point3f Max ()
   * @brief Return the maximum point.
   * @return 
   * @exception none
   * @details 
  */
  auto Max () const noexcept -> Point3f;

  /*!
   * @fn void Merge (const Bounds3f)
   * @brief 
   * @param[in] 
   * @return 
   * @exception none
   * @details 
  */
  auto Merge (const Bounds3f& bounds) -> void;

  /*!
   * @fn void Merge (const Point3f)
   * @brief 
   * @param[in] 
   * @return 
   * @exception none
   * @details 
   */
  auto Merge (const Point3f& p) -> void;

  /*!
   * @fn void SetMin (Param)
   * @brief 
   * @param[in] p
   *
   * @return 
   * @exception none
   * @details 
  */
  auto SetMin (const Point3f& p) noexcept -> void;

  /*!
   * @fn void SetMax ()
   * @brief Set 
   * @param[in] p
   * @return 
   * @exception none
   * @details 
  */
  auto SetMax (const Point3f& p) noexcept -> void;

  /*!
   * @fn void SetMax ()
   * @brief Compute surface area, then return it.
   * @return 
   * @exception none
   * @details 
   */
  auto SurfaceArea () const noexcept -> Float;

  /*!
   * @fn std ToString ()
   * @brief 
   * @return 
   * @exception none
   * @details 
   */
  auto ToString () const noexcept -> std::string;

  /*!
   * @fn bool IsIntersect (const)
   * @brief 
   * @param[in] ray
   *    
   * @return 
   * @exception none
   * @details 
   */
  auto IsIntersect (const Ray& ray) const noexcept -> bool;

private:
  Point3f min_;
  Point3f max_;
}; // class Bounds3f
/*
// ---------------------------------------------------------------------------
*/
auto Union (const Bounds3f& lhs, const Bounds3f& rhs) -> Bounds3f;
/*
// ---------------------------------------------------------------------------
*/
} // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _BOUNDS3F_H_

