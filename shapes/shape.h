#ifndef _SHAPE_H_
#define _SHAPE_H_

#include "../core/niepce.h"
#include "../core/interaction.h"
#include "../core/ray.h"
#include "../core/transform.h"
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
  Shape();
  Shape(const Transform* local_to_world,
        const Transform* world_to_local);
  virtual ~Shape();

  Shape(const Shape& shape) = default;
  Shape(Shape&&      shape) = default;

  auto operator = (const Shape& shape) -> Shape& = default;
  auto operator = (Shape&&      shape) -> Shape& = default;

  // Reture Surface Area
  virtual auto SurfaceArea() const -> Float = 0;

  // Get a bounding box at the local coordinate system
  virtual auto LocalBoundingBox() const -> BBox3f = 0;

  // Get a bounding box at the world coordinate system
  virtual auto WorldBoundingBox() const -> BBox3f = 0;

  // Check intersection with shape
  virtual auto IsIntersect(const Ray& ray, Float* t, SurfaceInteraction* surface) -> bool = 0;

 protected:
  std::shared_ptr<Transform> local_to_world_;
  std::shared_ptr<Transform> world_to_local_; // Inverse matrix of object_to_world

  // Does normal vector aim to inside ?
  // bool reverse_orient;
};

} // namespace niepce

#endif // _SHAPE_H_
