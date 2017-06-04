#ifndef _BVH_NODE_
#define _BVH_NODE_

#include "../core/niepce.h"
#include "../primitives/primitive.h"
#include "../geometries/boundingbox3.h"

namespace niepce
{

class BVHNode
{
 public:
  using Nodes         = std::array<std::shared_ptr<BVHNode>, 2>; // Available on interior node
  using PrimitivePtrs = std::vector<std::shared_ptr<Primitive>>; // Available on leaf node

 public:
  enum class Axis
  {
    kX    = 0,
    kY    = 1,
    kZ    = 2,
    kNone = 3
  };

 public:
  BVHNode();
  virtual ~BVHNode();
  BVHNode(const BVHNode& node) = default;
  BVHNode(BVHNode&& node)      = default;


  // ---------------------------------------------------------------------------
  // BVHNode public operators
  // ---------------------------------------------------------------------------
 public:
  auto operator = (const BVHNode& node) -> BVHNode& = default;
  auto operator = (BVHNode&& node)      -> BVHNode& = default;


  // ---------------------------------------------------------------------------
  // BVHNode public methods
  // ---------------------------------------------------------------------------
 public:
  // Initialize leafs with nullptr and parameters
  auto InitLeafs(const Bounds3f& b, const PrimitivePtrs& p) -> void;

  // Set leaf pointer
  auto InitInterior(Axis axis,
                    std::unique_ptr<BVHNode>&& node1,
                    std::unique_ptr<BVHNode>&& node2) -> void;

  // Return leaf node or not
  auto IsLeaf() -> bool;

  // Return interior node or not
  auto IsInterior() -> bool;


  // ---------------------------------------------------------------------------
  //BVHNode data
  // ---------------------------------------------------------------------------
  Bounds3f      bounds;
  Nodes         nodes;      // Left node and right node     (Available interior node)
  Axis          split_axis; // Used for traversal algorithm (Available interior node)
  PrimitivePtrs primitives; // Shared pointer, it has primitive or primitives (Avalilable leaf node)
}; // class BVHNode

}  // namespace niepce

#endif // _BVH_NODE_
