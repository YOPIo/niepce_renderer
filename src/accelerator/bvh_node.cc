/*!
 * @file bvh_node.cc
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#include "bvh_node.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
auto BvhNode::IsInterior () const noexcept -> bool
{
  return (childlen[0] != nullptr && childlen[1] != nullptr);
}
/*
// ---------------------------------------------------------------------------
*/
auto BvhNode::IsLeaf () const noexcept -> bool
{
  return (childlen[0] == nullptr && childlen[1] == nullptr);
}
/*
// ---------------------------------------------------------------------------
*/
auto BvhNode::InitializeInterior (BvhNode *c1, BvhNode *c2) -> void
{
  childlen[0] = c1;
  childlen[1] = c2;
  bounds = Union (childlen[0]->bounds, childlen[1]->bounds);
  num_primitives = 0;
}
/*
// ---------------------------------------------------------------------------
*/
auto BvhNode::InitializeLeaf (int offset, int n, const Bounds3f &bounds) -> void
{
  this->offset = offset;
  this->bounds = bounds;
  this->num_primitives = n;
  childlen[0] = childlen[1] = nullptr;
}
/*
// ---------------------------------------------------------------------------
*/
} // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
