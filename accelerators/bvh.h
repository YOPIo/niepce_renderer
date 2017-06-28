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

class BVH : public AggregatePrimitive
{
 private:
  using Aggregate = std::vector<std::shared_ptr<Primitive>>;

 public:
  /* BVH constructors */
  BVH () = delete;
  BVH (const Aggregate& primitives);
  virtual ~BVH ();

  BVH (const BVH&  bvh) = default;
  BVH (      BVH&& bvh) = default;


  /* BVH operators*/
 public:
  auto operator = (const BVH&  bvh) -> BVH& = default;
  auto operator = (      BVH&& bvh) -> BVH& = default;


  /* BVH public methods */
 public:
  auto WorldBounds () const -> Bounds3f override;
  auto LocalBounds () const -> Bounds3f override;
  auto IsIntersect (const Ray& ray, Interaction* interaction) const -> bool override;
  auto SurfaceArea () const -> Float override;

#ifdef Debug
  auto Dump (const char* filename) const -> void;
#endif // Debug


  /* BVH private methods */
 private:
  auto RecursiveConstruct (Aggregate* aggregate) -> std::shared_ptr<BVHNode>;
  auto CreateLeaf         (Aggregate* aggregate) -> std::shared_ptr<BVHNode>;

  /* BVH private data */
 private:
  std::shared_ptr<BVHNode> root_;
}; // class BVH


}  // namespace niepce

#endif // _BVH_H_
