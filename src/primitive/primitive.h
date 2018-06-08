/*!
 * @file primitive.h
 * @brief 
 * @author Masashi Yoshida
 * @date 2018/5/5
 * @details 
 */
#ifndef _PRIMITIVE_H_
#define _PRIMITIVE_H_
/*
// ---------------------------------------------------------------------------
*/
#include "../core/niepce.h"
#include "../core/intersection.h"
#include "../material/material.h"
#include "../shape/sphere.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
//! ----------------------------------------------------------------------------
//! @class Primitive
//! @brief
//! @details
//! ----------------------------------------------------------------------------
class Primitive
{
public:
  //! The default class constructor.
  Primitive () = default;

  //! The constructor takes shape pointer and material pointer.
  Primitive
  (
   const std::shared_ptr <Shape>&    shape,
   const std::shared_ptr <Material>& material
  );

  //! The copy constructor of the class.
  Primitive (const Primitive& primitive) = default;

  //! The move constructor of the class.
  Primitive (Primitive&& primitive) = default;

  //! The default class destructor.
  virtual ~Primitive () = default;

  //! The copy assignment operator of the class.
  auto operator = (const Primitive& primitive) -> Primitive& = default;

  //! The move assignment operator of the class.
  auto operator = (Primitive&& primitive) -> Primitive& = default;

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
   const Ray& ray,
   Intersection* intersection
  )
  const noexcept -> bool;

  /*!
   * @fn std Shape ()
   * @brief 
   * @return 
   * @exception none
   * @details 
  */
  auto Shape () const noexcept -> const std::shared_ptr <niepce::Shape>;

  /*!
   * @fn std Material ()
   * @brief 
   * @return 
   * @exception none
   * @details 
  */
  auto Material () const noexcept -> const std::shared_ptr <niepce::Material>;

private:
  std::shared_ptr <niepce::Shape>    shape_prt_;
  std::shared_ptr <niepce::Material> material_ptr_;
}; // class Primitive
/*
// ---------------------------------------------------------------------------
// Helper function for primitive
// ---------------------------------------------------------------------------
*/
auto CreatePrimitive
(
 const std::shared_ptr <Shape>&    shape,
 const std::shared_ptr <Material>& material
)
  -> std::shared_ptr <Primitive>;
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _PRIMITIVE_H_
