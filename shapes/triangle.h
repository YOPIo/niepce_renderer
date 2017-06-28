#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include "../core/niepce.h"
#include "../core/transform.h"
#include "../geometries/ray.h"
#include "../geometries/boundingbox3.h"
#include "vertex.h"
#include "triangle_mesh.h"
#include "shape.h"

namespace niepce
{

class Triangle : public Shape
{
  /* Triangle constructors */
 public:
  Triangle ();
  Triangle (const std::shared_ptr<Vertex>& v0,
            const std::shared_ptr<Vertex>& v1,
            const std::shared_ptr<Vertex>& v2);
  Triangle (const std::array<std::shared_ptr<Vertex>, 3>& v);
  ~Triangle ();

  Triangle (const Triangle&  t) = default;
  Triangle (      Triangle&& t) = default;


  /* Triangle public operators */
 public:
  auto operator = (const Triangle& t) -> Triangle& = default;
  auto operator = (Triangle&& t)      -> Triangle& = default;


  /* Triangle override methods */
 public:
  // Return surface area of triangle
  auto SurfaceArea () const -> Float override;

  // Return bounding box in object coordinate
  auto LocalBounds () const -> Bounds3f override;

  // Return bounding box in world coordinate
  auto WorldBounds () const -> Bounds3f override;

  // Intersection test
  auto IsIntersect (const Ray&   ray,
                    Interaction* surface) const -> bool override;


  /* Triangle private data */
 private:
  std::array<std::shared_ptr<Vertex>, 3> vertices_;
}; // class Triangle


}  // namespace niepce

#endif // _TRIANGLE_H_
