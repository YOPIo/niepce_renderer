#ifndef _RAY_H_
#define _RAY_H_

#include "niepce.h"
#include "vector3.h"

// ---------------------------------------------------------------------------
// Ray
// ---------------------------------------------------------------------------
struct Ray
{
  Ray()
  {}
  Ray(const Vector3f org_, const Vector3f &dir_) :
      origin(org_), direction(dir_)
  {}
  ~Ray()
  {}
  Vector3f origin, direction;
};

#endif // _RAY_H_
