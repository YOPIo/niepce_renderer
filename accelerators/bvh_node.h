#ifndef _BVH_NODE_
#define _BVH_NODE_

#include "../core/niepce.h"
#include "../primitives/primitive.h"
#include "../geometries/boundingbox3.h"

namespace niepce
{

// ---------------------------------------------------------------------------
// Interface of BVH node
// ---------------------------------------------------------------------------
class BVHNode
{
  /* BVHNode constructors */
 public:
  BVHNode ();
  BVHNode (const Bounds3f& bounds);
  virtual ~BVHNode ();

  BVHNode (const BVHNode& node) = default;
  BVHNode (BVHNode&& node)      = default;


  /* BVHNode operators */
  auto operator = (const BVHNode& node) -> BVHNode& = default;
  auto operator = (BVHNode&& node)      -> BVHNode& = default;


  /* Interface methods */
  virtual auto IsInterior       () const -> bool     = 0;
  virtual auto IsLeaf           () const -> bool     = 0;

  /* BVHNode public methods */
  auto SetBoundingBox (const Bounds3f& bounds)       -> void;
  auto GetBoundingBox ()                       const -> Bounds3f;


  /* BHVNode protected data */
 protected:
  Bounds3f bounds_; // Bounding box in world coordinate system
}; // class BVHNode


// ---------------------------------------------------------------------------
// Interiror node
// ---------------------------------------------------------------------------
class Interior : public BVHNode
{
 private:
  using Childlen = std::array<std::shared_ptr<BVHNode>, 2>;

 public:
  /* Interior constructors */
  Interior ();
  Interior (const Bounds3f&    bounds,
                  unsigned int split_axis,
            const Childlen&    childlen);
  virtual ~Interior ();

  Interior (const Interior& inter) = default;
  Interior (Interior&& inter)      = default;


  /* Interiror operators */
 public:
  auto operator = (const Interior& inter) -> Interior& = default;
  auto operator = (Interior&& inter)      -> Interior& = default;
  auto operator [] (unsigned int idx) const -> std::shared_ptr<BVHNode>;
  auto operator [] (unsigned int idx)       -> std::shared_ptr<BVHNode>&;


  /* Interiror override methods */
 public:
  auto IsInterior       () const -> bool     override;
  auto IsLeaf           () const -> bool     override;

  /* Interior public methods */
 public:
  auto SetChildNode (unsigned int idx, const std::shared_ptr<BVHNode>& node) -> void;


  /* Interior private data */
 private:
  Childlen     childlen_;
  unsigned int split_axis_; // 0:x, 1:y, 2:z
}; // class Interior

// ---------------------------------------------------------------------------
// Leaf node
// ---------------------------------------------------------------------------
class Leaf : public BVHNode
{
 private:
  using Aggragate = std::vector<std::shared_ptr<Primitive>>;

  /* Leaf constructors */
 public:
  Leaf ();
  Leaf (const Bounds3f& bounds,
        unsigned int    first,
        unsigned int    last);
  virtual ~Leaf ();

  Leaf (const Leaf& leaf) = default;
  Leaf (Leaf&& leaf)      = default;

  /* Leaf operators */
 public:
  auto operator = (const Leaf& leaf) -> Leaf& = default;
  auto operator = (Leaf&& leaf)      -> Leaf& = default;

  /* Leaf override methods */
 public:
  auto IsInterior       () const -> bool override;
  auto IsLeaf           () const -> bool override;

  /* Leaf public methods */


  /* Leaf private data */
  // This leaf node refer primitives_[first] to primitives_[last]
  // Also this leaf node does not have pointer(s) in directly
  unsigned int first_;
  unsigned int last_;
  Aggragate primitives_;
}; // class Leaf

}  // namespace niepce

#endif // _BVH_NODE_
