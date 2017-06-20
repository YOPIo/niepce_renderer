#include "bvh_node.h"

namespace niepce
{

// ---------------------------------------------------------------------------
// BVHNode
// ---------------------------------------------------------------------------
BVHNode::BVHNode () :
    bounds_()
{}

BVHNode::BVHNode (const Bounds3f& bounds) :
    bounds_(bounds)
{}

BVHNode::~BVHNode ()
{}

auto BVHNode::SetBoundingBox (const Bounds3f &bounds) -> void
{
  bounds_ = bounds;
}

auto BVHNode::GetBoundingBox () const -> Bounds3f
{
  return bounds_;
}


// ---------------------------------------------------------------------------
// BHV interior node
// ---------------------------------------------------------------------------
Interior::Interior () :
    BVHNode  (),
    childlen_( {nullptr, nullptr} )
{}

Interior::Interior (const Bounds3f&    bounds,
                          unsigned int split_axis,
                    const Childlen&    childlen) :
    BVHNode     (bounds),
    split_axis_ (split_axis),
    childlen_   (childlen)
{}

Interior::~Interior ()
{}

auto Interior::operator [] (unsigned int idx) const -> std::shared_ptr<BVHNode>
{
#ifdef DEBUG
  try { return childlen_.at(idx); }
  catch (const std::out_of_range& e) {}
#else
  return childlen_[idx];
#endif
}

auto Interior::operator [] (unsigned int idx) -> std::shared_ptr<BVHNode>&
{
#ifdef DEBUG
  try { return childlen_.at(idx); }
  catch (const std::out_of_range& e) {}
#else
  return childlen_[idx];
#endif
}

auto Interior::IsInterior () const -> bool
{
  return true;
}

auto Interior::IsLeaf () const -> bool
{
  return false;
}

auto Interior::SetChildNode (unsigned int idx, const std::shared_ptr<BVHNode>& node) -> void
{
#ifdef DEBUG
  try   { childlen_.at(idx) = node; }
  catch (const std::out_of_range& e) {}
#else
  childlen_[idx] = node;
#endif
}


// ---------------------------------------------------------------------------
// BVH leaf node
// ---------------------------------------------------------------------------
Leaf::Leaf () :
    BVHNode ()
{}

Leaf::Leaf (const Bounds3f& bounds,
            unsigned int    first,
            unsigned int    last) :
    BVHNode (bounds),
    first_  (first),
    last_   (last)
{}

Leaf::~Leaf ()
{}

auto Leaf::IsInterior () const -> bool
{
  return false;
}

auto Leaf::IsLeaf () const -> bool
{
  return true;
}


}  // namespace niepce
