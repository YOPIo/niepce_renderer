/*!
 * @file bvh_node.h
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#ifndef _BVH_NODE_H_
#define _BVH_NODE_H_
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
/*
// ---------------------------------------------------------------------------
*/
struct BvhNode
{
  Bounds3f bounds;
  BvhNode* childlen[2];

  // How many node primitive has.
  // 0 -> internal, otherwise -> leaf.
  int num_primitives;

  // Beginning of index.
  int offset;

  /*!
   * @fn bool IsLeaf ()
   * @brief 
   * @return 
   * @exception none
   * @details 
   */
  auto IsLeaf () const noexcept -> bool;

  /*!
   * @fn bool IsInterior ()
   * @brief 
   * @return 
   * @exception none
   * @details 
   */
  auto IsInterior () const noexcept -> bool;

  /*!
   * @fn void InitializeLeaf ()
   * @brief 
   * @param[in] offset
   *
   * @param[in] n
   *
   * @param[in] bounds
   *
   * @return 
   * @exception none
   * @details 
   */
  auto InitializeLeaf (int offset, int n, const Bounds3f& bounds) -> void;

  /*!
   * @fn void InitializeInterior ()
   * @brief 
   * @param[in] split_axis
   *
   * @param[in] c1
   *
   * @param[in] c2
   *
   * @return 
   * @exception none
   * @details 
   */
  auto InitializeInterior (BvhNode* c1, BvhNode* c2) -> void;
};
/*
// ---------------------------------------------------------------------------
*/
struct BvhBucket
{
  int count = 0;
  Bounds3f bounds;
};
/*
// ---------------------------------------------------------------------------
*/
} // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _BVH_NODE_H_

