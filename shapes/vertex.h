#ifndef _VERTEX_H_
#define _VERTEX_H_

#include "../core/niepce.h"
#include "../core/transform.h"
#include "../geometries/point2.h"
#include "../geometries/point3.h"
#include "../geometries/vector2.h"
#include "../geometries/vector3.h"
#include "../geometries/normal3.h"

namespace niepce
{

// ---------------------------------------------------------------------------
// NOTE: All of vertex are stored in world space coordinate
// ---------------------------------------------------------------------------
struct Vertex
{
  /* Vertex constructors */
  Vertex ();
  // Vertex is located in world coordinate system
  Vertex (const Point3f&  position,
          const Normal3f& normal,
          const Point2f&  uv);
  // Vertex is located in object coordinate system, use this constructor
  /*
  Vertex (const Transform& local_to_world,
          const Point3f&   position,
          const Normal3f&  normal,
          const Point2f&   uv);
  */
  virtual ~Vertex ();
  Vertex (const Vertex&  tm) = default;
  Vertex (      Vertex&& tm) = default;


  /* Vertex  operators*/
  auto operator = (const Vertex&  tm) -> Vertex& = default;
  auto operator = (      Vertex&& tm) -> Vertex& = default;


  /* Vertex data */
  Point3f  position; // Vertex positions
  Normal3f normal;   // Normal vectors at the vertex position
  Point2f  uv;       // Parametric (u, v) values at the vertex position
};

}  // namespace niepce

#endif // _VERTEX_H_
