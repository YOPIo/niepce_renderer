/*!
 * @file aggregation.h
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#ifndef _AGGREGATION_H_
#define _AGGREGATION_H_
/*
// ---------------------------------------------------------------------------
*/
#include "../core/niepce.h"
#include "../primitive/primitive.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
//! ----------------------------------------------------------------------------
//! @class Aggregation
//! @brief
//! @details
//! ----------------------------------------------------------------------------
class Aggregation
{
public:
  //! The default class constructor.
  Aggregation () = default;

  //! The copy constructor of the class.
  Aggregation (const Aggregation& aggregation) = default;

  //! The move constructor of the class.
  Aggregation (Aggregation&& aggregation) = default;

  //! The default class destructor.
  virtual ~Aggregation () = default;

  //! The copy assignment operator of the class.
  auto operator = (const Aggregation& aggregation) -> Aggregation& = default;

  //! The move assignment operator of the class.
  auto operator = (Aggregation&& aggregation) -> Aggregation& = default;

public:
  /*!
   * @fn void AddPrimitive (const)
   * @brief Add the primitive to the internal data.
   * @param[in] primitive
   * @return 
   * @exception none
   * @details
   */
  auto AddPrimitive (const std::shared_ptr<Primitive>& primitive) noexcept -> void;

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

private:
  std::vector <std::shared_ptr <Primitive>> primitives_;
}; // class Aggregation
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _AGGREGATION_H_
