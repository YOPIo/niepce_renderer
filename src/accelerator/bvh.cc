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
}
/*
// ---------------------------------------------------------------------------
*/
auto Bvh::Build (const std::vector<std::shared_ptr<Primitive>>& primitives)
  -> void
{
  // Initialize the BvhPrimitiveInfo.
  std::vector <PrimitiveInfo> info (primitives.size ());
  for (int i = 0; i < primitives.size (); ++i)
  {
    const auto& shape = primitives[i]->Shape ();
    info[i] = PrimitiveInfo (i, shape->Bounds ());
  }

  // Create copy of primitives.
  std::vector <std::shared_ptr <Primitive>> tmp;

  // Construct BVH structure.
  root_ = RecursiveBuild (info, 0, primitives.size (), tmp);
  primitives_.swap (tmp);
}
/*
// ---------------------------------------------------------------------------
*/
auto Bvh::RecursiveBuild
(
 std::vector <PrimitiveInfo>& info,
 std::size_t begin,
 std::size_t end,
 std::vector <std::shared_ptr <Primitive>>& primitives
)
  -> BvhNode*
{
  // All of the nodes are managed by MemoryArena.
  auto node = memory_.Allocate <BvhNode> ();

  // Incrementing the number of nodes.
  ++total_nodes_;

  // Compute bounds of all primitives.
  Bounds3f bounds;
  for (int i = begin; i < end; ++i) { bounds = Union (bounds, info[i].bounds); }

  // Compute the number of primitive.
  auto num_primitive = end - begin;

  // ---------------------------------------------------------------------------
  // Function to create a leaf node.
  // ---------------------------------------------------------------------------
  auto create_leaf = [&] ()
  {
    const int offset = primitives.size ();
    for (int i = begin; i < end; ++i)
    {
      const int index = info[i].primitive_index;
      primitives.push_back (primitives_[i]);
    }
    node->InitializeLeaf (offset, num_primitive, bounds);
  };

  // ---------------------------------------------------------------------------
  // Create leaf node.
  // ---------------------------------------------------------------------------
  if (num_primitive <= 1)
  {
    create_leaf ();
    return node;
  }

  // ---------------------------------------------------------------------------
  // Create interior node.
  // ---------------------------------------------------------------------------

  // Ready to compute SAH.
  // Compute centroid bounds each.
  Bounds3f centroid_bounds;
  for (int i = begin; i < end; ++i) { centroid_bounds.Merge (info[i].centroid); }

  // Get maximum component (x, y, or z).
  // Primitives will be split by maximum component axis.
  int dimension = 0;
  const auto d = centroid_bounds.Diagonal ();
  if (d.X () > d.Y () && d.X () > d.Z ()) { dimension = 0; }
  else if (d.Y () > d.Z ()) { dimension = 1; }
  else { dimension = 2; }

  auto middle = (begin + end) / 2;
  if (centroid_bounds.Max ()[middle]  == centroid_bounds.Min ()[middle])
  {
    // This is a unusual case.
    // All centroid points are at the same position.
    // Create leaf node.
    create_leaf ();
    return node;
  }

  // ---------------------------------------------------------------------------
  // Find a partition to split primitives based on SAH algorithm.
  // ---------------------------------------------------------------------------

  // Initialize buckets.
  static constexpr int kNumBucket = 12;
  BvhBucket bucket[kNumBucket];
  for (int i = begin; i < end; ++i)
  {
    const auto min = centroid_bounds.Min ();
    const auto max = centroid_bounds.Max ();
    const auto p   = info[i].centroid;

    auto idx = static_cast <int> ((p - min)[dimension] / (max - min)[dimension]);
    if (idx == kNumBucket) { idx = idx - 1; }

    bucket[idx].count++;
    bucket[idx].bounds = Union (bucket[i].bounds, info[i].bounds);
  }

  // Compute casts for splitting.
  Float cost[kNumBucket - 1];
  for (int i = 0; i < kNumBucket; ++i)
  {
    Bounds3f b1, b2;
    int count1 = 0, count2 = 0;
    for (int j = 0; j <= i; ++j)
    {
      b1 = Union (b1, bucket[j].bounds);
      count1 += bucket[j].count;
    }
    for (int j = i + 1; j < kNumBucket; ++j)
    {
      b1 = Union (b1, bucket[j].bounds);
      count2 += bucket[j].count;
    }
    cost[i] = 0.125f + (count1 * b1.SurfaceArea () + count2 * b2.SurfaceArea ())
            / bounds.SurfaceArea ();
  }

  // Find minimum cost from buckets.
  Float min_cost = cost[0];
  int split_bucket_idx = 0;
  for (int i = 1; i < kNumBucket; ++i)
  {
    if (cost[i] < min_cost)
    {
      min_cost = cost[i];
      split_bucket_idx = i;
    }
  }

  Float leaf_cost = num_primitive;
  if (max_primitives_ < num_primitive || min_cost > leaf_cost)
  {
    // -------------------------------------------------------------------------
    // Continue to split.
    // -------------------------------------------------------------------------
    auto comp = [=] (const PrimitiveInfo& info) -> bool
    {
      const auto min = centroid_bounds.Min ();
      const auto max = centroid_bounds.Max ();
      const auto p   = info.centroid;

      auto idx = static_cast <int> (((p - min) / (max - min))[dimension]);
      if (idx == kNumBucket) { idx = idx - 1; }

      return idx <= split_bucket_idx;
    };
    auto pos = std::partition (&info[begin], &info[end - 1] + 1, comp);
    middle = pos - &info[0];

    // Initialize the node as interior node.
    auto c1 = RecursiveBuild (info, begin,  middle, primitives);
    auto c2 = RecursiveBuild (info, middle, end,    primitives);
    node->InitializeInterior (c1, c2);
    return node;
  }

  // Otherwise, create leaf node.
  create_leaf ();
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
    if (node->IsInterior ())
    {
      // Current node is interior node.
      // Continue to traverse.
      Intersection tmp1, tmp2;
      auto t1 = RecursiveIsIntersect (node->childlen[0], ray, &tmp1);
      auto t2 = RecursiveIsIntersect (node->childlen[1], ray, &tmp2);
      if (!t1 && !t2) { return false; }
      // Compute nearest intersection point from ray origin.
      auto dist1 = tmp1.Distance (), dist2 = tmp2.Distance ();
      if (dist1 < dist2) { *intersection = tmp1; return true; }
      *intersection = tmp2; return true;
    }
    // Current node is leaf.
    // Find the intersection point by binary search.
    bool hit = false;
    Intersection tmp;
    for (int i = 0; i < node->num_primitives; ++i)
    {
      if (primitives_[node->offset + i]->IsIntersect (ray, &tmp))
      {
        if (tmp.Distance () < intersection->Distance ())
        {
          hit = true;
          *intersection = tmp;
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
} // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
