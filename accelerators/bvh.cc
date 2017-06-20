#include "bvh.h"

namespace niepce
{

BVH::BVH (const Aggregate& primitives) :
    primitives_(primitives)
{
  // Handling case
  if (primitives_.size() == 0)
  {
    std::cerr << "Error (BVH)" << std::endl;
    // Error:
    return ;
  }

  // Initialize primitive information array
  std::vector<BVHPrimitiveInfo> info (primitives_.size());
  for (int i = 0 ; i < info.size(); ++i)
  {
    info[i] = BVHPrimitiveInfo(i, primitives_[i]->WorldBounds());
  }

  // Create empty primitives vector
  // When a leaf nodes is created, Recursivebuild () method add the primitive(s)
  Aggregate ordered_aggregate (primitives_.size());

  // Build BVH with SAH algorithm
  unsigned int num_nodes = 0;
  root_ = RecursiveBuild (info, 0, info.size(), &ordered_aggregate, &num_nodes);


  // Finally, swapping 'ordered_aggregate' for 'primitves_'
  std::swap (primitives_, ordered_aggregate);
}

BVH::~BVH ()
{}

auto BVH::WorldBounds () const -> Bounds3f
{

}

auto BVH::LocalBounds () const -> Bounds3f
{

}

auto BVH::IsIntersect(const Ray &ray, Interaction* interaction) const -> bool
{

}

auto BVH::SurfaceArea () const -> Float
{

}

auto BVH::RecursiveBuild (std::vector<BVHPrimitiveInfo>& info,  // Number of data should be last - first
                          unsigned int                   first, // Where the data starts from
                          unsigned int                   last,  // Where the data end
                          Aggregate*                     ordered_aggregate,
                          unsigned int*                  num_nodes) -> std::shared_ptr<BVHNode>
{
  // Increasing number of node
  (*num_nodes)++;

  // Check handling case
  if (last < first)
  {
    // Error:
  }

  // Compute bounding box of all primitives in BVH node
  Bounds3f bounds;
  for (int i = first; i <= last; ++i)
  {
    bounds = Union (bounds, info[i].bounds);
  }

  std::shared_ptr<BVHNode> node;

  const unsigned int num_primitives = last - first + 1;

  // ---------------------------------------------------------------------------
  // Create a leaf node
  // ---------------------------------------------------------------------------

  if (num_primitives == 1)
  {
    // Compute index where a leaf node should refer to as first
    const unsigned int first_index = ordered_aggregate->size();
    // Compute index where a leaf ndoe should refer to as last
    const unsigned int last_index  = first_index + num_primitives;

    // Allocating a memory
    node.reset(new Leaf(bounds, first_index, last_index));

    // Store primitive(s) to 'ordered_aggregate'
    for (int i = first; i <= last; ++i)
    {
      // Get a primitive index
      const unsigned int primitive_index = info[i].primitive_number;
      ordered_aggregate->push_back (primitives_[primitive_index]);
    }
    return node;
  }

  // ---------------------------------------------------------------------------
  // Continue to build
  // BVH is built by SAH (surface area heuristic) algorithm
  // ---------------------------------------------------------------------------

  // Computing the largest range of the centroids of each primitive
  Bounds3f centroid_bounds;
  for (int i = first; i <= last; ++i)
  {
    centroid_bounds = Union (centroid_bounds, info[i].centroid);
  }

  // Choosing one of the three coordinate axes to use in partitioning
  const unsigned int partition_dimension = centroid_bounds.MaxExtent();

  // All of the centroid points are at the same position (unusual case)
  // Handling case, create leaf node
  if (centroid_bounds.Max()[partition_dimension] == centroid_bounds.Min()[partition_dimension])
  {
    // Compute index where a leaf node should refer to as first
    const unsigned int first_index = ordered_aggregate->size();
    // Compute index where a leaf ndoe should refer to as last
    const unsigned int last_index  = first_index + num_primitives;

    node.reset(new Leaf(bounds, first_index, last_index));

    // Store primitive(s) to 'ordered_aggregate'
    for (int i = first; i <= last; ++i)
    {
      // Get a 'primitives_' index
      const unsigned int primitive_index = info[i].primitive_number;
      ordered_aggregate->push_back (primitives_[primitive_index]);
    }
    return node;
  }

  // ---------------------------------------------------------------------------
  // Partition primitives into two groups
  // 1. Create buckets which store a number of primitive and its bounding box
  // 2. Initialize them (store that how many primitives and compute bounding box)
  // 3. Compute each cost
  // 4. Find a minimum cost and best plane to split
  // 5. Decide to creating a leaf node or continue to build
  // ---------------------------------------------------------------------------

  unsigned int middle = (last + first + 1) / 2;
  // Partition primitives using approximate SAH algorithm
  // See also section 4.3.2 in PBR
  if (num_primitives == 4)
  {
    // Partition primitives into equally sized
    const auto equally = [&partition_dimension](const BVHPrimitiveInfo& a, const BVHPrimitiveInfo& b)
                         {
                           return a.centroid[partition_dimension] < b.centroid[partition_dimension];
                         };
    std::nth_element(&info[first], &info[middle], &info[last] + 1, equally);
  }

  // 1. Create buckets which store a number of primitive and its bounding box
  // This is a kind of magic number, this number should be small because we will compurte $O(n^2)$
  constexpr unsigned int kNumBucket = 16;
  std::array<Bucket, kNumBucket> buckets;

  // 2. Initialize them (store that how many primitives and compute bounding box)
  for (int i = first; i <= last; ++i)
  {
    Float        distance = (info[i].centroid - bounds.Min())[partition_dimension];
    unsigned int idx      = distance / bounds.Diagonal()[partition_dimension] * kNumBucket;
    if (idx == kNumBucket) { idx -= 1; }
    buckets[idx].count++;
    buckets[idx].bounds = Union (buckets[idx].bounds, info[i].centroid);
  }

  /*
    Compute SAH cost
    There are two important values time it takes to traverse the interior node and time it
    takes to ray-object intersection
    Here as a constant values in niepce renderer
    constexpr Float kTraverseTime  = 1.0;
    constexpr Float kIntersectTime = 1.0;
  */

  // 3. Compute each cost
  std::array<Float, kNumBucket - 1> costs;
  for (int i = 0; i < kNumBucket - 1; ++i)
  {
    Bounds3f bounds1, bounds2;
    unsigned int cnt1 = 0;
    unsigned int cnt2 = 0;

    for (int j = 0; j <= i; ++j)
    {
      bounds1 =  Union (bounds1, buckets[j].bounds);
      cnt1    += buckets[j].count;
    }

    for (int j = i; j <= kNumBucket; ++j)
    {
      bounds2 =  Union (bounds2, buckets[j].bounds);
      cnt2    += buckets[j].count;
    }

    // Compute cost
    costs[i] = (cnt1 * bounds1.SurfaceArea() + cnt2 * bounds2.SurfaceArea()) / bounds.SurfaceArea();
  }

  // 4. Find a minimum cost and best plane to split
  Float        min_cost = costs[0];
  for (int i = 1; i < kNumBucket - 1; ++i)
  {
    if (costs[i] < min_cost) { min_cost = costs[i]; }
  }

  // 5. Decide to creating a leaf node or continue to build
  const Float leaf_cost = num_primitives;
  if (leaf_cost < min_cost)
  {
    // Create a leaf node
    // Compute index where a leaf node should refer to as first
    const unsigned int first_index = ordered_aggregate->size();
    // Compute index where a leaf ndoe should refer to as last
    const unsigned int last_index  = first_index + num_primitives;

    node.reset(new Leaf(bounds, first_index, last_index));

    // Store primitive(s) to 'ordered_aggregate'
    for (int i = first; i <= last; ++i)
    {
      // Get a 'primitives_' index
      const unsigned int primitive_index = info[i].primitive_number;
      ordered_aggregate->push_back (primitives_[primitive_index]);
    }
    return node;
  }
  // Continue to build
  auto partition = [=](const BVHPrimitiveInfo& i)
                   {
                     Float        distance = (i.centroid - bounds.Min())[partition_dimension];
                     unsigned int idx      =
                                  distance / bounds.Diagonal()[partition_dimension] * kNumBucket;

                     if (idx == kNumBucket) { idx -= 1; }
                     return costs[idx] < min_cost;
                   };
  auto pos = std::partition(&info[first], &info[last], partition);
  middle = pos - &info[0];

  // Allocating interior node memory
  const std::array<std::shared_ptr<BVHNode>, 2> childlen =
      { RecursiveBuild(info, first,  middle - 1, ordered_aggregate, num_nodes),
        RecursiveBuild(info, middle, last,       ordered_aggregate, num_nodes) };

  node.reset( new Interior(bounds,
                           partition_dimension,
                           childlen));
  return node;
}

}  // namespace niepce
