#include "bvh.h"

namespace niepce
{

BVH::BVH (const Aggregate& primitives){
  // Handling case
  if (primitives.size() == 0)
  {
    std::cerr << "Error (BVH)" << std::endl;
    // Error:
    return ;
  }

  Aggregate aggregate (primitives);

  // Build BVH with SAH algorithm
  unsigned int num_nodes = 0;
  root_ = RecursiveConstruct (&aggregate);
}

BVH::~BVH ()
{}

auto BVH::WorldBounds () const -> Bounds3f
{

}

auto BVH::LocalBounds () const -> Bounds3f
{

}

auto BVH::IsIntersect (const Ray &ray, Interaction* interaction) const -> bool
{
  bool is_hit = false;
  std::shared_ptr<BVHNode> node = root_;
  while (true)
  {
    if (node->IsIntersect (ray))
    {
      if (node->IsLeaf ())
      {
        const std::shared_ptr<Leaf> leaf = std::dynamic_pointer_cast<Leaf> (node);

        break;
      }
      else
      {
        const std::shared_ptr<Interior> inter = std::dynamic_pointer_cast<Interior> (node);
        const std::shared_ptr<BVHNode>  left  = inter->LeftNode  ();
        const std::shared_ptr<BVHNode>  right = inter->RightNode ();
        if (left->IsIntersect (ray))
        {
          node = std::move (left);
          continue;
        }
        if (right->IsIntersect (ray))
        {
          node = std::move (right);
          continue;
        }
        // No hit with childlen bounding boxes
        break;
      }
    }
  }

  return is_hit;
}

auto BVH::SurfaceArea () const -> Float
{

}

auto BVH::RecursiveConstruct (Aggregate* aggregate) -> std::shared_ptr<BVHNode>
{
  // Compute bounding box of all primitives in 'aggregate'
  Bounds3f bounds;
  for (auto& p : *aggregate)
  {
    bounds = Union (bounds, p->WorldBounds ());
  }

  // ---------------------------------------------------------------------------
  // Create a leaf node if size of 'aggregate' is one
  // ---------------------------------------------------------------------------
  if (aggregate->size () == 1)
  {
    return std::move ( CreateLeaf (aggregate) );
  }

  // ---------------------------------------------------------------------------
  // Continue to build
  // BVH is built by SAH (surface area heuristic) algorithm
  // ---------------------------------------------------------------------------

  // Decide a split axis
  const unsigned int axis = bounds.MaxExtent ();

  // ---------------------------------------------------------------------------
  // Partition primitives into two groups
  // 1. Sort by split axis
  // 2. Computing each cost
  // 3. Find a minimum cost
  // 4. Decide to creating a leaf node or continue to build
  // ---------------------------------------------------------------------------

  constexpr unsigned int num_leafs = 4; // Magic number ??
  // Need not to divide more
  if (aggregate->size() <= num_leafs)
  {
    return std::move ( CreateLeaf (aggregate) );
  }

  // 1. Sort by split axis
  auto sorting =
      [axis](const std::shared_ptr<Primitive>& p0, const std::shared_ptr<Primitive>& p1)
      {
        const Bounds3f bounds0 = p0->WorldBounds ();
        const Bounds3f bounds1 = p1->WorldBounds ();
        return bounds0.Centroid ()[axis] < bounds1.Centroid ()[axis];
      };
  std::sort (aggregate->begin(), aggregate->end(), sorting);

  // 2. Computing each cost
  Float* costs = new Float [aggregate->size ()];
  for (int i = 0; i < aggregate->size (); ++i)
  {
    Bounds3f bounds0, bounds1;
    for (int j = 0; j < i; ++j)
    {
      bounds0 = Union (bounds0, (*aggregate)[j]->WorldBounds ());
    }
    for (int j = i; j < aggregate->size (); ++j)
    {
      bounds1 = Union (bounds1, (*aggregate)[j]->WorldBounds ());
    }
    costs[i] = (static_cast<Float>(i)                      * bounds0.SurfaceArea () +
                static_cast<Float>(aggregate->size () - i) * bounds1.SurfaceArea ())
        / bounds.SurfaceArea ();
  }

  // 3. Find a minimum cost
  int   middle   = 0;
  Float min_cost = aggregate->size ();
  for (int i = 1; i < aggregate->size (); ++i)
  {
    if (costs[i] < min_cost)
    {
      middle   = i;
      min_cost = costs[i];
    }
  }
  delete [] costs;

  // 4. Decide to creating a leaf node or continue to build
  // Create leaf
  if (min_cost == aggregate->size ())
  {
    return std::move ( CreateLeaf (aggregate) );
  }

  // Continue to build
  Aggregate left  (aggregate->begin(), aggregate->begin() + middle);
  Aggregate right (aggregate->begin() + middle, aggregate->end());

  /*
    Debug
  Bounds3f b0, b1;
  for (auto& pri : left)
  {
    b0 = Union (b0, pri->WorldBounds ());
  }
  for (auto& pri : right)
  {
    b1 = Union (b1, pri->WorldBounds ());
  }
  std::cerr << "leaf  node size: " << left.size  () << ", surface area: " << b0.SurfaceArea () << std::endl;
  std::cerr << "right node size: " << right.size () << ", surface area: " << b1.SurfaceArea () << std::endl;
  */

  // Create interior node
  std::shared_ptr<BVHNode> left_node  = RecursiveConstruct (&left);
  std::shared_ptr<BVHNode> right_node = RecursiveConstruct (&right);
  std::shared_ptr<BVHNode> interior (new Interior (bounds, left_node, right_node));

  return std::move (interior);
}

#ifdef Debug
auto BVH::Dump (const char* filename) const -> void
{
  std::ifstream ifs (filename);
  // Todo: Implementation
  ifs.close ();
}
#endif


auto BVH::CreateLeaf (Aggregate* aggregate) -> std::shared_ptr<BVHNode>
{
  // Compute bounding box
  Bounds3f bounds;
  for (auto& p : *aggregate)
  {
    bounds = Union (bounds, p->WorldBounds());
  }
  std::shared_ptr<BVHNode> leaf ( new Leaf (bounds, *aggregate) );
  return std::move (leaf);
}

}  // namespace niepce
