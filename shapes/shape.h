#ifndef _SHAPE_H_
#define _SHAPE_H_

#include "../core/niepce.h"
#include "../core/interaction.h"
#include "../geometries/ray.h"
#include "../core/transform.h"
#include "../geometries/boundingbox2.h"
#include "../geometries/boundingbox3.h"
#include "../geometries/normal3.h"
#include "../geometries/point2.h"
#include "../geometries/point3.h"
#include "../geometries/point4.h"
#include "../geometries/vector2.h"
#include "../geometries/vector3.h"
#include "../geometries/vector4.h"

namespace niepce
{

class Shape
{
 public:
  Shape ();
  Shape (const Point3f& p); // Initialize with vertex position
  Shape (const std::shared_ptr<Transform>& local_to_world,
         const std::shared_ptr<Transform>& world_to_local);
  virtual ~Shape ();

  Shape (const Shape& shape) = default;
  Shape (Shape&&      shape) = default;

  auto operator = (const Shape& shape) -> Shape& = default;
  auto operator = (Shape&&      shape) -> Shape& = default;

  // ---------------------------------------------------------------------------
  // Shape override functions
  // ---------------------------------------------------------------------------
  // Reture Surface Area
  virtual auto SurfaceArea () const -> Float = 0;

  // Get a bounding box at the local coordinate system
  virtual auto LocalBounds () const -> Bounds3f = 0;

  // Get a bounding box at the world coordinate system
  virtual auto WorldBounds () const -> Bounds3f = 0;

  // Check intersection with shape
  virtual auto IsIntersect (const Ray&   ray,
                            Interaction* surface) const -> bool = 0;

 protected:
  std::shared_ptr<Transform> local_to_world_;
  std::shared_ptr<Transform> world_to_local_; // Inverse matrix of object_to_world

  // Does normal vector aim to inside ?
  // bool reverse_orient;
};

} // namespace niepce

#endif // _SHAPE_H_
