#include "bvh_node.h"

namespace niepce
{

BVHNode::BVHNode()
{}

BVHNode::~BVHNode()
{}

auto BVHNode::InitLeafs(const Bounds3f& b, const PrimitivePtrs& p) -> void
{
  bounds     = b;
  nodes[0]   = nullptr;
  nodes[1]   = nullptr;
  split_axis = Axis::kNone;
  primitives = p;
}

auto BVHNode::InitInterior(Axis axis,
                           std::unique_ptr<BVHNode>&& node1,
                           std::unique_ptr<BVHNode>&& node2) -> void
{
  bounds     = Bounds3f();
  nodes[0]   = std::move(node1);
  nodes[1]   = std::move(node2);
  split_axis = Axis::kNone;

}

inline auto BVHNode::IsLeaf() -> bool
{
  return (nodes[0] == nullptr && nodes[1] == nullptr);
}

inline auto BVHNode::IsInterior() -> bool
{
  return !(IsLeaf());
}

}  // namespace niepce
