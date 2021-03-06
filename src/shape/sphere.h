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
#include "../core/transform.h"
#include "../core/niepce.h"
#include "../core/point3f.h"
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
  Sphere (const Transform &world_to_local, Float radius);

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

  /*!
   * @fn Bounds3f Bounds () const noexcept
   * @brief Return bound of this shape.
   * @return 
   * @exception none
   * @details 
  */
  auto Bounds () const noexcept -> Bounds3f override final;

  /*!
   * @fn Point3f Sample ()
   * @brief 
   * @return 
   * @exception none
   * @details
   */
  auto Sample (const Point2f& sample) const noexcept -> Point3f override final;

  /*!
   * @fn Return SurfaceArea ()
   * @brief 
   * @return 
   * @exception none
   * @details
   */
  auto SurfaceArea () const noexcept -> Float override final;

private:
  Float radius_;
}; // class Sphere
/*
// ---------------------------------------------------------------------------
// Helper function for sphere.
// ---------------------------------------------------------------------------
*/
auto CreateSphere
(
 const Transform &transform,
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
