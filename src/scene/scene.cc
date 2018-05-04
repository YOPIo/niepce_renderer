/*!
 * @file scene.cc
 * @brief 
 * @author Masashi Yoshida
 * @date 2018/5/5
 * @details 
 */
#include "scene.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
auto Scene::Intersect
(
 const Ray& ray,
 Intersection* intersection
)
const noexcept -> bool
{
  Float distance = kInfinity;
  for (const auto& primitive : primitives_)
  {
    // Intersection test.
    Intersection temp;
    if (primitive.IsIntersect (ray, &temp))
    {
      if (temp.Distance () < distance)
      {
        *intersection = temp;
        distance = temp.Distance ();
      }
    }
  }
  return distance != kInfinity;
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
