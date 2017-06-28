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

// ---------------------------------------------------------------------------
// Store a hit position, ray direction to hit position, normal at the position etc.
// ---------------------------------------------------------------------------
struct Interaction
{
  /*Constructors */
  Interaction ();
  Interaction (      Float     t,
               const Point3f&  p,
               const Vector3f& dir,
               const Normal3f& n);
  virtual ~Interaction ();

  Interaction (const Interaction& interaction) = default;
  Interaction (Interaction&& interaction)      = default;


  /*Operators */
  auto operator = (const Interaction& interaction) -> Interaction& = default;
  auto operator = (Interaction&& interaction)      -> Interaction& = default;


  /* Interaction data */
  Float    t;         //
  Point3f  position;  // Hit position
  Vector3f direction; // Direction to hit position from origin of ray
  Normal3f normal;    // Normal at hit position
};

struct SurfaceInteraction : public Interaction
{
  /* Surfaceinteraction constructors */
  SurfaceInteraction ();
  SurfaceInteraction (Float t,
                      const Point3f&  pos,   const Vector3f& dir,
                      const Normal3f& n,     const Point2f&  _uv,
                      const Vector2f& _dpdu, const Vector2f& _dpdv,
                      const Normal3f& _dndu, const Normal3f& _dndv);
  virtual ~SurfaceInteraction ();

  SurfaceInteraction (const SurfaceInteraction& surface) = default;
  SurfaceInteraction (SurfaceInteraction&& surface)      = default;


  /* Surfaceinteraction operators */
  auto operator = (const SurfaceInteraction& surface) -> SurfaceInteraction& = default;
  auto operator = (SurfaceInteraction&& surface)      -> SurfaceInteraction& = default;


  /* SurfaceInteraction data */
  Point2f  uv;         // Texture coordinate
  Vector2f dpdu, dpdv; // Partial derivative of position
  Normal3f dndu, dndv; // Partial derivative of normal

  /*
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
