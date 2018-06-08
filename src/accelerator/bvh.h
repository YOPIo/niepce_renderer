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
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
//! ----------------------------------------------------------------------------
//! @class BvhNode
//! @brief
//! @details
//! ----------------------------------------------------------------------------
struct BvhNode
{
  //! The default class constructor.
  BvhNode ();

  //! The copy constructor of the class.
  BvhNode (const BvhNode& node) = default;

  //! The move constructor of the class.
  BvhNode (BvhNode&& node) = default;

  //! The default class destructor.
  virtual ~BvhNode () = default;

  //! The copy assignment operator of the class.
  auto operator = (const BvhNode& node) -> BvhNode& = default;

  //! The move assignment operator of the class.
  auto operator = (BvhNode&& node) -> BvhNode& = default;

  //! @brief Bound of this node.
  Bounds3f bounds;

  //! @brief Index of child node.
  unsigned int left_child;
  unsigned int right_child;

  //! @brief Valid only leaf node
  std::vector <std::shared_ptr<Primitive>> primitives;
}; // class BvhNode
//! ----------------------------------------------------------------------------
//! @class Bvh
//! @brief
//! @details
//! ----------------------------------------------------------------------------
class Bvh
{
  typedef std::vector <std::shared_ptr<Primitive>> Primitives;

public:
  //! The default class constructor.
  Bvh () = default;

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
  auto Build (Primitives& primitives) -> void;

private:
  /*
   * @fn Return ComputeBounds (const std::vector <std::shared_ptr <Primitives>>&)
   * @brief 
   * @param[in] primitives
   *
   * @return Bounds3f
   * @exception none
   * @details 
  */
  auto ComputeBoundsFrom (const Primitives& primitives)
    const noexcept -> Bounds3f;

  /*!
   * @fn Return CreateLeafNode (const std::vector <std::shared_ptr <Primitives>>&)
   * @brief 
   * @param[in] primitives
   *    
   * @return Bounds3f
   * @exception none
   * @details 
   */
  auto CreateLeafNode (const Primitives& primitives) const noexcept -> BvhNode;

  /*!
   * @fn Return ComputeBounds (const std::vector <std::shared_ptr <Primitives>>&)
   * @brief 
   * @param[in] primitives
   *
   * @return Bounds3f
   * @exception none
   * @details 
  */
  auto SortPrimitivesByAxis (Primitives* primitives, int axis)
    const noexcept -> void;

private:
  std::vector <BvhNode> nodes_;
  std::vector <std::shared_ptr <Primitive>> primitives_;
}; // class Bvh
/*
// ---------------------------------------------------------------------------
*/
} // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _BVH_H_

