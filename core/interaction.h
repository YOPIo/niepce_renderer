#ifndef _INTERACTION_H_
#define _INTERACTION_H_

#include "niepce.h"
#include "../shapes/shape.h"
#include "../geometries/point2.h"
#include "../geometries/point3.h"
#include "../geometries/vector2.h"
#include "../geometries/vector3.h"
#include "../geometries/normal3.h"

namespace niepce
{

struct Interaction
{
  Point3f  position;  // Hit position
  Vector3f direction; // Direction to hit position from origin of ray
  Normal3f normal;    // Normal at hit position

  // Vector3f p_error;
  // Vector3f nagative_direction;
};

struct SurfaceInteraction : public Interaction
{
  Point2f  uv;         // For texture
  Vector2f dpdu, dpdv; // Partial derivative of point 'p'
  Normal3f dndu, dndv; // Partial derivative of normal 'n'
  const std::shared_ptr<Shape> shape = nullptr;

  /*
    For bump mapping
  struct shading
  {
    Normal3f n;
    Vector2f dpdu, dpdv;
    Normal3f dndu, dndv;
  };
  */
};


}  // namespace niepce

#endif // _INTERACTION_H_
