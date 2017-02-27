#ifndef _SHAPE_H_
#define _SHAPE_H_

#include "../core/normal3.h"
#include "../core/niepce.h"
#include "../core/point2.h"
#include "../core/point3.h"
#include "../core/point4.h"
#include "../core/ray.h"
#include "../core/vector2.h"
#include "../core/vector3.h"
#include "../core/vector4.h"

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
  virtual auto IsIntersect(const Ray& ray) -> bool = 0;
  virtual auto IsIntersectWithAlpah(const Ray& ray) -> bool = 0;

 public:
  std::shared_ptr<Transform> world;
  std::shared_ptr<Transform> local;
};


} // namespace niepce

#endif // _SHAPE_H_
