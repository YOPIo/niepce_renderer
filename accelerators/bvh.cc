#include "bvh.h"


namespace niepce
{

/*
  BVH constructor
  There are three step to BVH construction
  - Bounding box information about each primitive should be computed and stored in an array
  - Build BVH with split methods (SAH, HLBVH)
  - Result of construction is binary tree
    It holds pointers to its leaf nodes
*/
BVH::BVH(const PrimitivePtrs& primitives)
{
  // No construction
  if (primitives.size() == 0) { return ; }

  PrimitivePtrs p(primitives);

  // Build BVH with calling _BuildRecursively()_ or _BuildHVBVH()_
  // They return a pointer to the root of the tree
  root_ = BuildRecursive(p);
}

BVH::~BVH()
{}


// ---------------------------------------------------------------------------
// BVH private methods
// ---------------------------------------------------------------------------
/*
  Construct BVH by SAH methods
  Reference paper
  'Ray Tracing Deformable Scenes using Dynamic Bounding Volume Hierarchies'
*/
auto BVH::BuildRecursive(PrimitivePtrs& primitives) -> std::unique_ptr<BVHNode>
{
  // The time to compute a ray-triangle intersection (constant variable)
  constexpr Float kTriangleTime = 1.0f;
  // The time to compute a ray-AABB intersection (constant variable)
  constexpr Float kBoundsTime   = 1.0f;

  // Create BVHNode
  std::unique_ptr<BVHNode> node(new BVHNode());

  // Precompute boundingboxes for each primitives and compute surface area of all primitives
  std::vector<Bounds3f> boundingboxes(primitives.size());
  Bounds3f bounds;
  for (int i = 0; i < primitives.size(); ++i)
  {
    boundingboxes[i] = primitives[i]->WorldBoundingBox();
    bounds = Union(bounds, boundingboxes[i]);
  }
  const Float surface_area_of_node = bounds.SurfaceArea();

  // Cost of making a leaf
  Float best_cost = kTriangleTime * primitives.size();

  // 0:x-axis, 1:y-axis, 2:z-axis, -1:Unknown
  int best_axis = -1;

  // What
  int best_split_index = -1;

  bounds = Bounds3f();
  // Loop for x, y and z axis
  for (int axis = 0; axis < 3; ++axis)
  {
    // Sort primitives using centroid of boxes in current axis
    auto lambda = [&axis](const Bounds3f& b1, const Bounds3f& b2)
                  {
                    return b1.Centroid()[axis] > b2.Centroid()[axis];
                  };
    std::sort(boundingboxes.begin(), boundingboxes.end(), lambda);

    // Create surface area list
    std::vector<Float> surface_area_list1(boundingboxes.size() + 1, kInfinity);
    std::vector<Float> surface_area_list2(boundingboxes.size() + 1, kInfinity);


    // Sweep from left
    // Compute surface area of each patern
    for (int i = 0; i <= primitives.size(); ++i)
    {
      if (i == 0)
      {
        bounds = Union(bounds, boundingboxes[i - 1]);
        continue;
      }
      // Compute each surface area
      surface_area_list1[i] = bounds.SurfaceArea();
      bounds = Union(bounds, boundingboxes[i - 1]);
    }

    bounds = Bounds3f();
    // Sweep from right
    for (int i = primitives.size(); i >= 0; --i)
    {
      if (i == primitives.size())
      {
        bounds = Union(bounds, boundingboxes[i - 1]);
        continue;
      }
      // Compute surface area
      surface_area_list2[i] = bounds.SurfaceArea();

      // Evaluate equation 2 (see papaers in detail)
      Float new_cost = 2 * kBoundsTime + (surface_area_list1[i] * surface_area_list1.size() +
                                          surface_area_list2[i] * surface_area_list2.size()) *
                       kTriangleTime / surface_area_of_node;

      // Check best cost
      if (new_cost < best_cost)
      {
        best_cost        = new_cost;
        best_axis        = axis;
        best_split_index = i;
      }

      bounds = Union(bounds, boundingboxes[i - 1]);
    }
  }

  if (best_axis == -1)
  {
    // Create leaf node
    node->InitLeafs(bounds, primitives);
    return std::move(node);
  }

  // Call this function again to build BVH
  // Sort again besed on best axis
  auto lambda = [&best_axis](const Bounds3f& b1, const Bounds3f& b2)
                {
                  return b1.Centroid()[best_axis] > b2.Centroid()[best_axis];
                };
  std::sort(boundingboxes.begin(), boundingboxes.end(), lambda);

  // Divide primitives
  PrimitivePtrs left_primitives(primitives.begin(), primitives.begin() + best_split_index);
  PrimitivePtrs right_primitives(primitives.begin() + best_split_index, primitives.end());

  // Create interior node
  node->InitInterior(static_cast<BVHNode::Axis>(best_axis), // Split axis
                     BuildRecursive(left_primitives),
                     BuildRecursive(right_primitives));

  return std::move(node);
}

auto BVH::BuildHLBVH() -> BVHNode*
{

}

}  // namespace niepce
