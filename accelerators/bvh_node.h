#ifndef _BVH_NODE_
#define _BVH_NODE_

#include "../core/niepce.h"
#include "../primitives/primitive.h"
#include "../geometries/boundingbox3.h"
#include "../geometries/ray.h"

namespace niepce
{

// ---------------------------------------------------------------------------
// Interface of BVH node
// ---------------------------------------------------------------------------
class BVHNode
{
 private:
  typedef std::vector<std::shared_ptr<Primitive>> Aggregate;
  typedef std::array<std::shared_ptr<BVHNode>, 2> Childlen;
  /* BVHNode constructors */
 public:
  BVHNode ();
  // Constructor for leaf node
  BVHNode (const Bounds3f&  bounds,
           const Aggregate& aggregate);
  // Constructor for interior node
  BVHNode (const Bounds3f&                 bounds,
           const std::shared_ptr<BVHNode>& left,
           const std::shared_ptr<BVHNode>& right);
  virtual ~BVHNode ();

  BVHNode (const BVHNode& node) = default;
  BVHNode (BVHNode&& node)      = default;


  /* BVHNode operators */
  auto operator = (const BVHNode&  node) -> BVHNode& = default;
  auto operator = (      BVHNode&& node) -> BVHNode& = default;


  /* BVHNode public methods */
 public:
  auto InitLeaf     (const Bounds3f&  bounds,
                     const Aggregate& aggregate) -> void;

  auto InitInterior (const Bounds3f&                 bounds,
                     const std::shared_ptr<BVHNode>& left,
                     const std::shared_ptr<BVHNode>& right ) -> void;

  auto WorldBounds () const -> Bounds3f;
  auto IsInterior  () const -> bool;
  auto IsLeaf      () const -> bool;

  auto IsIntersect (const Ray& ray, Interaction* interaction) const -> bool;

  /* BHVNode protected data */
 protected:
  Bounds3f  bounds_; // Bounding box in world coordinate system
  Aggregate aggregate_;
  Childlen  childlen_;
}; // class BVHNode

}  // namespace niepce

#endif // _BVH_NODE_
