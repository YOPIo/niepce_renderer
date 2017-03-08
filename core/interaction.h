#ifndef _INTERACTION_H_
#define _INTERACTION_H_

#include "niepce.h"
#include "../geometries/point2.h"
#include "../geometries/point3.h"
#include "../geometries/vector2.h"
#include "../geometries/vector3.h"
#include "../geometries/normal3.h"

namespace niepce
{

class Shape;

/*
  Store a hit position, ray direction to hit position, normal at the position etc.
*/

class Interaction
{
 public:
  Interaction();
  Interaction(const Point3f&  _position,
              const Vector3f& _direction,
              const Normal3f& _normal);
  virtual ~Interaction();

  Interaction(const Interaction& interaction) = default;
  Interaction(Interaction&& interaction)      = default;

  auto operator = (const Interaction& interaction) -> Interaction& = default;
  auto operator = (Interaction&& interaction)      -> Interaction& = default;

 public:
  Point3f  position;  // Hit position
  Vector3f direction; // Direction to hit position from origin of ray
  Normal3f normal;    // Normal at hit position

  /*
    Unimplemented
    Vector3f p_error;
    Vector3f nagative_direction;
   */
};

class SurfaceInteraction : public Interaction
{
 public:
  SurfaceInteraction();
  SurfaceInteraction(const Point3f&  _position, const Vector3f& _direction,
                     const Normal3f& _normal,   const Point2f&  _uv,
                     const Vector2f& _dpdu,     const Vector2f& _dpdv,
                     const Normal3f& _dndu,     const Normal3f& _dndv);
  virtual ~SurfaceInteraction();

  SurfaceInteraction(const SurfaceInteraction& surface) = default;
  SurfaceInteraction(SurfaceInteraction&& surface)      = default;

  auto operator = (const SurfaceInteraction& surface) -> SurfaceInteraction& = default;
  auto operator = (SurfaceInteraction&& surface)      -> SurfaceInteraction& = default;

 public:
  Point2f  uv;         // For texture coordinate
  Vector2f dpdu, dpdv; // Partial derivative of point
  Normal3f dndu, dndv; // Partial derivative of normal

  /*
    Unimplemented
    struct shading  // For bump shading
    {
      Normal3f n;
      Vector2f dpdu, dpdv;
      Normal3f dndu, dndv;
    };
   */
};

}  // namespace niepce

#endif // _INTERACTION_H_
