#ifndef _BVH_H_
#define _BVH_H_

#include "bvh_node.h"
#include "bvh_boundingbox.h"
#include "../core/niepce.h"
#include "../core/interaction.h"
#include "../primitives/primitive.h"
#include "../geometries/ray.h"
#include "../geometries/boundingbox3.h"

namespace niepce
{


// ---------------------------------------------------------------------------
// BVH declarations
// ---------------------------------------------------------------------------
class BVH
{
 public:
  using PrimitivePtrs = std::vector<std::shared_ptr<Primitive>>;
  using BVHBounds     = std::vector<BVHBoundingBox>;

 public:
  BVH() = delete;
  BVH(const PrimitivePtrs& p);
  virtual ~BVH();

  BVH(const BVH& bvh) = default;
  BVH(BVH&& bvh)      = default;

  // ---------------------------------------------------------------------------
  // BVH public operators
  // ---------------------------------------------------------------------------
 public:
  auto operator = (const BVH& bvh) -> BVH& = default;
  auto operator = (BVH&& bvh)      -> BVH& = default;


  // ---------------------------------------------------------------------------
  // BVH public methods
  // ---------------------------------------------------------------------------
 public:
  // Get boundingb box
  auto WorldBounds() const -> Bounds3f;

  // Intersect test
  auto IsIntersect(const Ray& ray, Interaction* inter) -> bool;

  // ---------------------------------------------------------------------------
  // BVH private methods
  // ---------------------------------------------------------------------------
 private:
  // Build BVH using SAH split method
  auto BuildRecursive(PrimitivePtrs& primitives) -> std::unique_ptr<BVHNode>;

  // Build BVH using HLBVH split methods
  // todo: implementation
  auto BuildHLBVH() -> BVHNode* = delete;


  // ---------------------------------------------------------------------------
  // BVH private data
  // ---------------------------------------------------------------------------
 private:
  std::unique_ptr<BVHNode> root_;
}; // class BVH




}  // namespace niepce

#endif // _BVH_H_
