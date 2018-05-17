/*!
 * @file intersection.h
 * @brief 
 * @author Masashi Yoshida
 * @date 2018/5/5
 * @details 
 */
#ifndef _INTERSECTION_H_
#define _INTERSECTION_H_
/*
// ---------------------------------------------------------------------------
*/
#include "niepce.h"
#include "../shape/shape.h"
#include "point2f.h"
#include "point3f.h"
#include "vector3f.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
//! ----------------------------------------------------------------------------
//! @class Intersection
//! @brief 
//! @details All positions and vectors should be stored in world coodinate.
//! ----------------------------------------------------------------------------
class Intersection
{
public:
  //! The default class constructor.
  Intersection ();

  //! The copy constructor of the class.
  Intersection (const Intersection& intersection) = default;

  //! The move constructor of the class.
  Intersection (Intersection&& intersection) = default;

  //! The default class destructor.
  virtual ~Intersection () = default;

  //! The copy assignment operator of the class.
  auto operator = (const Intersection& intersection) -> Intersection& = default;

  //! The move assignment operator of the class.
  auto operator = (Intersection&& intersection) -> Intersection& = default;

public:
  /*!
   * @fn operator bool
   * @brief 
   * @details 
   * @return bool If ray intersect with a primitive, return true. Otherwise return false.
   * @exception none
   */
  explicit operator bool () const noexcept;

  /*!
   * @fn operator operator
   * @brief 
   * @details 
   * @return bool Logical not of operator bool.
   * @exception none
   */
  bool operator ! () const noexcept;

public:
  /*!
   * @fn Float Distance ()
   * @brief Return the distance from ray origin to intersection.
   * @return The distance as Float.
   * @exception none
   * @details
   */
  auto Distance () const noexcept -> Float;

  /*!
   * @fn bool IsIntersect ()
   * @brief Return ray intersected with the shape or not.
   * @return bool If ray intersects, return true. Otherwise return false.
   * @exception none
   * @details
   */
  auto IsIntersect () const noexcept -> bool;

  /*!
   * @fn std::shared_ptr <Material> Material ()
   * @brief Return the material pointer.
   * @return The material pointer which intersected shape has.
   * @exception none
   * @details If ray does not intersect with any shape, it will return nullptr.
   */
  auto Material () const noexcept -> const std::shared_ptr <niepce::Material>;

  /*!
   * @fn Vector3f Normal ()
   * @brief Return the normal vector at the intersection.
   * @return The normal vector.
   * @exception none
   * @details
   */
  auto Normal () const noexcept -> Vector3f;

  /*!
   * @fn Vector3f Tangent ()
   * @brief Return the tangent vector at the intersection.
   * @return 
   * @exception none
   * @details
   */
  auto Tangent () const noexcept -> Vector3f;

  /*!
   * @fn Vector3f Binormal ()
   * @brief Return the binormal vector at the intersection.
   * @return 
   * @exception none
   * @details
   */
  auto Binormal () const noexcept -> Vector3f;

  /*!
   * @fn Ray Outgoing ()
   * @brief Return the outgoing ray
   * @return The ray to the intersection.
   * @exception none
   * @details
   */
  auto Outgoing () const noexcept -> Vector3f;

  /*!
   * @fn const std::shared_ptr <Shape> Shape ()
   * @brief Return the shape pointer.
   * @return The shape pointer which intersected.
   * @exception none
   * @details
   */
  auto Shape () const noexcept -> const std::shared_ptr <Shape>;

  /*!
   * @fn Point2f Texcoord ()
   * @brief Return the texture coordinate.
   * @return Point2f
   * @exception none
   * @details
   */
  auto Texcoord () const noexcept -> Point2f;

  /*!
   * @fn Point3f Position ()
   * @brief Return the position of intersection in world coordinates.
   * @return The position of intersection.
   * @exception none
   * @details
   */
  auto Position () const noexcept -> Point3f;

  /*!
   * @fn void SetDistance (Float distance)
   * @brief Set the argument distance to internal data.
   * @param[in] distance The distance from ray origin to intersection.
   * @return void
   * @exception none
   * @details This method will make flag to true when ray intersects with the shape if distance is smaller than infinity.
   */
  auto SetDistance (Float distance) noexcept -> void;

  /*!
   * @fn void SetMaterial (const std::shared_ptr <niepce::Material>& material_ptr)
   * @brief Set the material pinter to internal data.
   * @param[in] std::shared_ptr <niepce::Material> The material pointer.
   * @return void
   * @exception none
   * @details
   */
  auto SetMaterial
  (const std::shared_ptr <niepce::Material>& material_ptr)
  noexcept -> void;


  /*!
   * @fn void SetNormal (const Vector3f& normal)
   * @brief Set the normal vector to internal data as normal vector in world
            coordinate. If normal vector sets, tangent vector and binormal
            vector will be calculated automatically.
   * @param[in] normal The normal vector at the shape.
   * @return void
   * @exception none
   * @details
   */
  auto SetNormal (const Vector3f& normal) noexcept -> void;

  /*!
   * @fn void SetOutgoing (const)
   * @brief Set the outgoing ray to the internal data.
   * @param[in] ray
   *    The outgoing ray to the intersection.
   * @return void
   * @exception none
   * @details
   */
  auto SetOutgoing (const Vector3f& outgoing) noexcept -> void;


  /*!
   * @fn Return SetShape (const)
   * @brief Set the shape pointer to internal data.
   * @param[in] std::shared_ptr <Shape>
   * @return void
   * @exception none
   * @details
   */
  auto SetShape (const std::shared_ptr <niepce::Shape>& shape) noexcept -> void;

  /*!
   * @fn void SetTexcoord (const)
   * @brief Set the texture coordinate to internal data.
   * @param[in] texcoord The texture coordinate.
   * @return void
   * @exception none
   * @details
   */
  auto SetTexcoord (const Point2f& texcoord) noexcept -> void;

  /*!
   * @fn void SetPosition (const Point3f& position)
   * @brief Set the argument position to internal data as intersection position
   *        in world coordinate.
   * @param[in] position The intersection position. The position should be in
   *            world coordinate.
   * @return 
   * @exception none
   * @details
   */
  auto SetPosition (const Point3f& position) noexcept -> void;

public:
  /*!
   * @fn Vector3f ToWorld (const Vector3f& v)
   * @brief Transform the vector in BSDF coordinate to world coordinates.
   * @param[in] v
   *    The vector in BSDF coordinates.
   * @return The vector in world coordinates.
   * @exception none
   * @details
   */
  auto ToWorld (const Vector3f& v) const noexcept -> Vector3f;

  /*!
   * @fn Vector3f ToLocal (const)
   * @brief Transform the vector in world coordinates to BSDF coordiantes.
   * @param[in] v
   *     The vector in world coordinates.
   * @return The vector in BSDF coordinates.
   * @exception none
   * @details
   */
  auto ToLocal (const Vector3f& v) const noexcept -> Vector3f;

private:
  //! The Distance parameter 't' from ray origin to intersection.
  Float distance_;

  //! The position of intersection.
  Point3f position_;

  //! The normal vector at the intersection.
  Vector3f normal_;

  //! The tangent vector at the intersection.
  Vector3f tangent_;

  //! The binormal vector at the intersection.
  Vector3f binormal_;

  //! The texture coordinate at the intersection.
  Point2f texcoord_;

  //! The material which intersected shape has.
  std::shared_ptr <niepce::Material> material_ptr_;

  //! The shape what ray intersected.
  std::shared_ptr <niepce::Shape> shape_ptr_;

  //! The ray to the intersection in world coordinates.
  Vector3f outgoing_;

}; // class Intersection
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _INTERSECTION_H_
