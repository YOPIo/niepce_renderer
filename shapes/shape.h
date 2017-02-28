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
  Shape(const Transform& world, const Transform& local);
  virtual ~Shape();

  Shape(const Shape& shape) = default;
  Shape(Shape&&      shape) = default;

  auto operator = (const Shape& shape) -> Shape& = default;
  auto operator = (Shape&&      shape) -> Shape& = default;

  // Reture Surface Area
  virtual auto SurfaceArea() -> Float = 0;

  // Check intersection with shape
  virtual auto IsIntersect(const Ray& ray, Float* t,
                           SurfaceInteraction* surface, bool use_alpah) -> bool = 0;
  virtual auto IsIntersectWithAlpah(const Ray& ray, bool use_alpha = true) -> bool;

 public:
  std::shared_ptr<Transform> world;
  std::shared_ptr<Transform> local;

  // Normal vector is defined or not?
  // bool reverse_orient;
};

} // namespace niepce

#endif // _SHAPE_H_
