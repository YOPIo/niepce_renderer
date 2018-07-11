/*!
 * @file bvh.h
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#ifndef _BVH_H_
#define _BVH_H_
/*
// ---------------------------------------------------------------------------
*/
#include "../core/niepce.h"
#include "../core/bounds3f.h"
#include "../core/memory.h"
#include "bvh_primitive_info.h"
#include "bvh_node.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
//! ----------------------------------------------------------------------------
//! @class Bvh
//! @brief
//! @details
//! ----------------------------------------------------------------------------
class Bvh
{
public:
  //! The default class constructor.
  Bvh () = default;

  //! The constructor takes primitives and the number of primitives in the node.
  Bvh
  (
   const std::vector <std::shared_ptr <Primitive>>& primitives,
   std::size_t max_primitives = 4
  );

  //! The copy constructor of the class.
  Bvh (const Bvh& bvh) = default;

  //! The move constructor of the class.
  Bvh (Bvh&& bvh) = default;

  //! The default class destructor.
  virtual ~Bvh () = default;

  //! The copy assignment operator of the class.
  auto operator = (const Bvh& bvh) -> Bvh& = default;

  //! The move assignment operator of the class.
  auto operator = (Bvh&& bvh) -> Bvh& = default;

public:
  /*!
   * @fn voi Build ()
   * @brief 
   * @return 
   * @exception none
   * @details 
  */
  auto Build (const std::vector <std::shared_ptr <Primitive>>& primitives)
    -> void;

  /*!
   * @fn bool IsIntersect (const Ray&, Intersection*)
   * @brief 
   * @param[in] ray
   *    
   * @param[out] intersection
   *    
   * @return 
   * @exception none
   * @details 
   */
  auto IsIntersect (const Ray& ray, Intersection* intersection)
    const noexcept -> bool;

private:
  /*!
   * @fn Return RecursiveBuild (const)
   * @brief 
   * @param[in] info
   *
   * @param[in] 
   *
   * @return 
   * @exception none
   * @details 
   */
  auto RecursiveBuild
  (
   std::vector <PrimitiveInfo>& info,
   std::size_t begin,
   std::size_t end,
   std::vector <std::shared_ptr <Primitive>>& primitives
  )
    -> BvhNode*;

  /*!
   * @fn bool RecursiveIsIntersect (const)
   * @brief 
   * @param[in] 
   * @param[out] 
   * @return 
   * @exception none
   * @details 
   */
  auto RecursiveIsIntersect
  (
   BvhNode* node,
   const Ray& ray,
   Intersection* intersection
  )
  const noexcept -> bool;

private:
  MemoryArena memory_;
  const std::size_t max_primitives_;
  std::vector <std::shared_ptr <Primitive>> primitives_;
  std::size_t total_nodes_;

  BvhNode* root_;
}; // class Bvh
/*
// ---------------------------------------------------------------------------
*/
} // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _BVH_H_

