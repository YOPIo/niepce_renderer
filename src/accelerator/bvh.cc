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
// BVH definitions
// ---------------------------------------------------------------------------
*/
Bvh::Bvh
(
 const std::vector <std::shared_ptr <Primitive>>& primitives,
 std::size_t max_primitives
) :
  primitives_     (primitives),
  max_primitives_ (std::min (static_cast<std::size_t> (64), max_primitives)),
  memory_ (1024 * 1024),
  total_nodes_ (0)
{
  Build (primitives_);
#ifdef DEBUG
  Dump (2);
#endif
}
/*
// ---------------------------------------------------------------------------
*/
auto Bvh::Build (const std::vector<std::shared_ptr<Primitive>>& primitives)
  -> void
{
  /*
  // Initialize the BvhPrimitiveInfo.
  std::vector <PrimitiveInfo> info (primitives.size ());
  for (int i = 0; i < primitives.size (); ++i)
  {
    const auto& shape = primitives[i]->Shape ();
    info[i] = PrimitiveInfo (i, shape->Bounds ());
  }
  */

  // Create copy of primitives.
  std::vector <std::shared_ptr <Primitive>> tmp (primitives);

  primitives_.clear ();

  // Construct BVH structure.
  root_ = RecursiveBuild (tmp, primitives_);

  std::cout << primitives_.size() << std::endl;
}
/*
// ---------------------------------------------------------------------------
*/
auto Bvh::RecursiveBuild
(
 std::vector <std::shared_ptr <Primitive>>& primitives,
 std::vector <std::shared_ptr <Primitive>>& ordered
)
  -> BvhNode*
{

  const auto num_primitives = primitives.size ();

  // All of the nodes are managed by MemoryArena.
  auto node = memory_.Allocate <BvhNode> ();

  // Compute bounds of all primitives.
  Bounds3f bounds;
  for (const auto &p : primitives)
  {
    bounds = Union (bounds, p->Shape ()->Bounds ());
  }

  // Handle case.
  if (num_primitives <= 4)
  {
    const auto offset = ordered.size ();
    for (int i = 0; i < num_primitives; ++i)
    {
      const auto p = primitives[i];
      ordered.push_back (p);
      node->InitializeLeaf (offset, num_primitives, bounds);
    }
    return node;
  }

  Float best_cost  = num_primitives;
  int   best_axis  = -1; // x : 0, y : 1, z : 2
  int   best_index = num_primitives * 0.5;
  Float surface_area = bounds.SurfaceArea ();

  for (auto axis = 0; axis < 3; ++axis)
  {
    // Sort primitives
    std::sort (primitives.begin (), primitives.end (),
               [&axis]
               (const std::shared_ptr <Primitive> &lhs,
                const std::shared_ptr <Primitive> &rhs) -> bool
               {
                 const auto &lcenter = lhs->Shape ()->Bounds ().Center ();
                 const auto &rcenter = rhs->Shape ()->Bounds ().Center ();
                 return lcenter[axis] < rcenter[axis];
               });

    std::vector <std::shared_ptr <Primitive>> s1, s2 (primitives);
    Bounds3f s1_bounds;
    Bounds3f s2_bounds;

    // List of surface area.
    std::vector <Float> s1_surface (num_primitives + 1, kInfinity);
    std::vector <Float> s2_surface (num_primitives + 1, kInfinity);

    for (int i = 0; i <= num_primitives; ++i)
    {
      s1_surface[i] = std::fabs (s1_bounds.SurfaceArea ());
      if (s2.size () > 0)
      {
        const auto p = s2.front ();
        s1.push_back (p);
        s2.erase (s2.begin ());
        s1_bounds = Union (s1_bounds, p->Shape ()->Bounds ());
      }
    }

    for (int i = num_primitives; i >= 0; --i)
    {
      s2_surface[i] = std::fabs (s2_bounds.SurfaceArea ());
      if (s1.size () > 0 && s2.size () > 0)
      {
        // Compute SAH cost
        const auto cost = 2.0 + (s1_surface[i] * s1.size ()
                        + s2_surface[i] * s2.size ()) / surface_area;
        if (cost < best_cost)
        {
          best_cost  = cost;
          best_axis  = axis;
          best_index = i;
        }
      }

      if (s1.size () > 0)
      {
        const auto p = s1.back ();
        s2.insert (s2.begin (), p);
        s1.pop_back ();
        s2_bounds = Union (s2_bounds, p->Shape ()->Bounds ());
      }
    }
  }

  if (best_axis == -1)
  {
    const auto offset = ordered.size ();
    for (int i = 0; i < num_primitives; ++i)
    {
      const auto p = primitives[i];
      ordered.push_back (p);
      node->InitializeLeaf (offset, num_primitives, bounds);
    }
    return node;
  }

  // Create interior node.
  std::sort (primitives.begin (), primitives.end (),
             [&best_axis]
             (const std::shared_ptr <Primitive> &lhs,
              const std::shared_ptr <Primitive> &rhs) -> bool
             {
               const auto &lcenter = lhs->Shape ()->Bounds ().Center ();
               const auto &rcenter = rhs->Shape ()->Bounds ().Center ();
               return lcenter[best_axis] < rcenter[best_axis];
             });
  std::vector <std::shared_ptr <Primitive>> left
    (primitives.begin (), primitives.begin () + best_index);
  std::vector <std::shared_ptr <Primitive>> right
    (primitives.begin () + best_index, primitives.end ());

  const auto left_node  = RecursiveBuild (left,  ordered);
  const auto right_node = RecursiveBuild (right, ordered);
  node->InitializeInterior (left_node, right_node);
  return node;
}
/*
// ---------------------------------------------------------------------------
*/
auto Bvh::IsIntersect (const Ray& ray, Intersection* intersection)
  const noexcept -> bool
{
  return (RecursiveIsIntersect (root_, ray, intersection));
}
/*
// ---------------------------------------------------------------------------
*/
auto Bvh::RecursiveIsIntersect
(
 BvhNode* node,
 const Ray& ray,
 Intersection* intersection
)
  const noexcept -> bool
{
  // Ray intersection test with node's bounds.
  if (node->bounds.IsIntersect (ray))
  {
    // -------------------------------------------------------------------------
    // Interior node.
    // -------------------------------------------------------------------------
    if (node->IsInterior ())
    {
      // Current node is interior node.
      // Continue to traverse.
      Intersection tmp1, tmp2;
      auto t1 = RecursiveIsIntersect (node->childlen[0], ray, &tmp1);
      auto t2 = RecursiveIsIntersect (node->childlen[1], ray, &tmp2);

      if (!t1 && !t2)
      {
        return false;
      }

      // Compute nearest intersection point from ray origin.
      auto dist1 = tmp1.Distance ();
      auto dist2 = tmp2.Distance ();
      if (dist1 < dist2)
      {
        *intersection = tmp1;
        return true;
      }

      // Only ray intersect with childlen 1.
      *intersection = tmp2;
      return true;
    }

    // -------------------------------------------------------------------------
    // Current node is leaf.
    // -------------------------------------------------------------------------
    bool hit = false;
    Intersection tmp;
    // Find the intersection point by binary search.
    for (int i = 0; i < node->num_primitives; ++i)
    {
      if (primitives_[node->offset + i]->IsIntersect (ray, &tmp))
      {
        if (tmp.Distance () > kEpsilon &&
            tmp.Distance () < intersection->Distance ())
        {
          hit = true;
          *intersection = tmp;
          intersection->SetPrimitive (primitives_[node->offset + i]);
        }
      }
    }
    return hit;
  }

  // Ray does not intersect with bounds.
  return false;
}
/*
// ---------------------------------------------------------------------------
*/
#ifdef DEBUG
// Traverse : zero origin (root)
auto Bvh::Dump (int traverse) -> void
{
  std::cout << "dump" << std::endl;
  DumpRecursive (root_, traverse, 0);
}
/*
// ---------------------------------------------------------------------------
*/
auto Bvh::DumpRecursive (BvhNode *node, int traverse, int depth) -> void
{
  if (depth == traverse)
  {
    const auto min = node->bounds.Min ();
    const auto max = node->bounds.Max ();
    std::cout << "[[" << min.X () << "," << min.Y () << ", "
              << min.Z () << "], ";
    std::cout << "[" << max.X () << "," << max.Y () << ", "
              << max.Z () << "]]" << std::endl;;
    return ;
  }

  if (node->childlen[0] != nullptr)
  {
    DumpRecursive (node->childlen[0], traverse, depth + 1);
  }
  if (node->childlen[1] != nullptr)
  {
    DumpRecursive (node->childlen[1], traverse, depth + 1);
  }
}
#endif // DEBUG
/*
// ---------------------------------------------------------------------------
*/
} // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
