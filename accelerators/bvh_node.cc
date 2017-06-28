#include "bvh_node.h"

namespace niepce
{

BVHNode::BVHNode ()
{}

BVHNode::BVHNode (const Bounds3f&  bounds,
                  const Aggregate& aggregate) :
    bounds_    (bounds),
    aggregate_ (aggregate),
    childlen_  ( {nullptr, nullptr} )
{}

BVHNode::BVHNode (const Bounds3f&  bounds,
                  const std::shared_ptr<BVHNode>& left,
                  const std::shared_ptr<BVHNode>& right) :
    bounds_   (bounds),
    childlen_ ( {left, right} )
{}

auto BVHNode::InitLeaf (const Bounds3f& bounds, const Aggregate& aggregate) -> void
{
  bounds_ = bounds;
  if (!aggregate_.empty ())
  {
    aggregate_.clear ();
    aggregate_ = aggregate;
  }
  childlen_[0].reset ();
  childlen_[1].reset ();
}

auto BVHNode::InitInterior (const Bounds3f&                 bounds,
                            const std::shared_ptr<BVHNode>& left,
                            const std::shared_ptr<BVHNode>& right) -> void
{
  bounds_ = bounds;
  if (!aggregate_.empty ())
  {
    aggregate_.clear ();
  }
  childlen_[0] = std::move (left);
  childlen_[1] = std::move (right);
}

auto BVHNode::WorldBounds () const -> Bounds3f
{
  return bounds_;
}

auto BVHNode::IsInterior () const -> bool
{
  if (aggregate_.empty ()     &&
      childlen_[0] != nullptr &&
      childlen_[1] != nullptr)
  {
    return true;
  }
  return false;
}

auto BVHNode::IsLeaf () const -> bool
{
  if (aggregate_.size () > 0  &&
      childlen_[0] == nullptr &&
      childlen_[1] == nullptr)
  {
    return true;
  }
  return false;
}

auto BVHNode::IsIntersect (const Ray& ray, Interaction* interaction) const -> bool
{
  // Leaf node check
  if (aggregate_.empty ()     &&
      childlen_[0] != nullptr &&
      childlen_[1] != nullptr)
  {
    // Node state is interior
    return false;
  }

  bool is_hit = false;
  for (auto& p : aggregate_)
  {
    if (p->IsIntersect(ray, interaction))
    {
      is_hit = true;
    }
  }

  return is_hit;
}


}  // namespace niepce
