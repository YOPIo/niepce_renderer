#ifndef _BVH_H_
#define _BVH_H_

#include "../core/niepce.h"
#include "../primitives/primitive.h"
#include "../primitives/aggregate_primitive.h"
#include "../materials/material.h"
#include "bvh_node.h"
#include "bvh_primitive_info.h"
#include "bvh_bucket.h"

// ---------------------------------------------------------------------------
// TODO List:
// - Write a 'CreateLeaf()' method when building a BVH
// ---------------------------------------------------------------------------

namespace niepce
{

auto BuildBVH (std::vector<std::shared_ptr<Primitive>> prims) -> std::shared_ptr<Primitive>;

class BVH : public AggregatePrimitive
{
 private:
  using Aggregate = std::vector<std::shared_ptr<Primitive>>;
  using Root      = std::shared_ptr<BVHNode>;

 public:
  /* BVH constructors */
  BVH () = delete;
  BVH (const Aggregate& primitives);
  virtual ~BVH ();

  BVH (const BVH&  bvh) = default;
  BVH (      BVH&& bvh) = default;


  /* BVH operators*/
 public:
  auto operator = (const BVH& bvh) -> BVH& = default;
  auto operator = (BVH&& bvh)      -> BVH& = default;


  /* BVH public methods */
 public:
  auto WorldBounds () const -> Bounds3f override;
  auto LocalBounds () const -> Bounds3f override;
  auto IsIntersect (const Ray& ray, Interaction* interaction) const -> bool override;
  auto SurfaceArea () const -> Float override;

  /* BVH private methods */
 private:
  auto RecursiveBuild (std::vector<BVHPrimitiveInfo>& info,
                       unsigned int                   first,
                       unsigned int                   last,
                       Aggregate*                     ordered_aggregate,
                       unsigned int*                  num_nodes) -> std::shared_ptr<BVHNode>;


  /* BVH private data */
 private:
  Root      root_;       // Root node of BVH
  Aggregate primitives_; // Leaf nodes refers to this data
}; // class BVH


}  // namespace niepce

#endif // _BVH_H_
