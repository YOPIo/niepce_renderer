/*!
 * @file bvh.cc
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#include "bvh.h"
#include "../core/bounds3f.h"
#include "../primitive/primitive.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
BvhNode::BvhNode ()
{}
/*
// ---------------------------------------------------------------------------
*/
auto BvhNode::InitializeAsLeaf
(
 const Primitives& primitives,
 const Bounds3f&   bounds
)
-> void
{
  primitives_ = primitives;
  right_ = nullptr;
  left_  = nullptr;
  bounds_ = bounds;
}
/*
// ---------------------------------------------------------------------------
*/
auto BvhNode::InitializeAsInternal
(
 const Bounds3f& bounds,
 BvhNode* right,
 BvhNode* left
) -> void
{
  primitives_.clear ();
  right_ = right;
  left_  = left;
}
/*
// ---------------------------------------------------------------------------
*/
auto Bvh::Build
(
 Primitives&  primitives,
 MemoryArena& memory
)
  -> BvhNode*
{
  const unsigned int num_primitive = primitives.size ();

  // Compute bounding box. (aabb)
  const Bounds3f pbounds = ComputeBoundsFromPrimitives (primitives);

  // Compute the surface area for the primitive.
  const Float parea = pbounds.SurfaceArea ();

  // Interim best cost.
  Float best_cost = primitives.size ();

  // Find a axis to split primitives.
  int best_axis = -1;

  // Find a index to 
  int best_index = 0;

  // If a number of primitive less than 4, create leaf node.
  if (num_primitive <= 4)
  {
    return CreateLeafNode (primitives, pbounds, memory);
  }

  for (int axis = 0; axis < 3; ++axis)
  {
    // Sort primitives by center position of bounds each component.
    SortPrimitivesByAxis (&primitives, axis);

    std::pair <std::vector <Float>, std::vector <Float>> area;
    area.first.resize (num_primitive, kInfinity);
    area.second.resize (num_primitive, kInfinity);

    std::pair <Bounds3f, Bounds3f> bounds;
    bounds.first  = Bounds3f ();
    bounds.second = pbounds;

    // Compute surface area, divide by axis.
    for (int i = 0; i <= num_primitive; ++i)
    {
      int j = num_primitive - i - 1;
      area.first[i]  = std::fabs (bounds.first.SurfaceArea ());
      area.second[j] = std::fabs (bounds.second.SurfaceArea ());
      if (i < num_primitive)
      {
        bounds.first.Merge (primitives[i]->Shape ()->Bounds ());
        continue;
      }
      if (j > 0)
      {
        bounds.second.Merge (primitives[j]->Shape ()->Bounds ());
      }
    }

    // Evaluate SAH cost from surface area.
    for (int i = 0; i <= num_primitive; ++i)
    {
      const Float n1 = i;
      const Float n2 = num_primitive - 1;
      const Float cost = 2.0 + area.first[i]  / parea * n1
                             + area.second[i] / parea * n2;
      if (cost < best_cost)
      {
        best_cost  = cost;
        best_axis  = axis;
        best_index = i;
      }
    }
  } // End of loop

  if (best_axis == -1)
  {
    // Create leaf node.
    return CreateLeafNode (primitives, pbounds, memory);
  }
  // Continue to split.

  // Sort by best axis again.
  SortPrimitivesByAxis (&primitives, best_axis);

  // Split primitives.
  Primitives lp (primitives.cbegin (), primitives.cbegin () + best_index);
  Primitives rp (primitives.cbegin () + best_index, primitives.cend ());

  // Recall method
  BvhNode* right = Build (lp, memory);
  BvhNode* left  = Build (rp, memory);

  // Create internal node.
  return CreateInternalNode (pbounds, right, left, memory);
}
/*
// ---------------------------------------------------------------------------
*/
auto Bvh::ComputeBoundsFromPrimitives (const Primitives& primitives)
  const noexcept -> Bounds3f
{
  Bounds3f res;
  for (const auto& p : primitives)
  {
    const auto& shape = p->Shape ();
    res.Merge (shape->Bounds ());
  }
  return res;
}
/*
// ---------------------------------------------------------------------------
*/
auto Bvh::CreateLeafNode
(
 const Primitives& primitives,
 const Bounds3f&   bounds,
 MemoryArena&      memory
)
  const -> BvhNode*
{
  BvhNode* node = memory.Allocate<BvhNode> ();
  node->InitializeAsLeaf (primitives, bounds);
  return node;
}
/*
// ---------------------------------------------------------------------------
*/
auto Bvh::CreateInternalNode
(
 const Bounds3f& bounds,
 BvhNode* right,
 BvhNode* left,
 MemoryArena& memory
)
  -> BvhNode*
{
  BvhNode* node = memory.Allocate <BvhNode> ();
  node->InitializeAsInternal (bounds, right, left);
  return node;
}
/*
// ---------------------------------------------------------------------------
*/
auto Bvh::SortPrimitivesByAxis (Primitives *primitives, int axis)
  const noexcept -> void
{
  std::sort (primitives->begin (), primitives->end (),
             [&]
             (
              const std::shared_ptr <Primitive>& p1,
              const std::shared_ptr <Primitive>& p2
             )
             {
               // Comparing by center position of each axis.
               const Point3f c1 = p1->Shape ()->Bounds ().Center ();
               const Point3f c2 = p2->Shape ()->Bounds ().Center ();
               return c1.At (axis) < c2.At (axis);
             });
}
/*
// ---------------------------------------------------------------------------
*/
} // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
