/*!
 * @file sphere.h
 * @brief 
 * @author Masashi Yoshida
 * @date 2018/5/5
 * @details 
 */
#ifndef _SPHERE_H_
#define _SPHERE_H_
/*
// ---------------------------------------------------------------------------
*/
#include "shape.h"
#include "../core/niepce.h"
#include "../math/point3f.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
//! ----------------------------------------------------------------------------
//! @class Sphere
//! @brief
//! @details
//! ----------------------------------------------------------------------------
class Sphere final : public Shape
{
public:
  //! The default class constructor.
  Sphere () = delete;

  //! The constructor takes radius and position.
  Sphere (Float radius, const Point3f& p);

  //! The copy constructor of the class.
  Sphere (const Sphere& sphere) = default;

  //! The move constructor of the class.
  Sphere (Sphere&& sphere) = default;

  //! The default class destructor.
  virtual ~Sphere () = default;

  //! The copy assignment operator of the class.
  auto operator = (const Sphere& sphere) -> Sphere& = default;

  //! The move assignment operator of the class.
  auto operator = (Sphere&& sphere) -> Sphere& = default;

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
  auto IsIntersect
  (
   const Ray& ray, // outgoing
   Intersection* intersection
  )
  const noexcept -> bool override;

private:
  Float   radius_;
  Point3f center_;
}; // class Sphere
/*
// ---------------------------------------------------------------------------
// Helper function for sphere.
// ---------------------------------------------------------------------------
*/
auto CreateSphere
(
 const Point3f& position,
 Float radius
)
-> std::shared_ptr <Shape>;
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _SPHERE_H_
