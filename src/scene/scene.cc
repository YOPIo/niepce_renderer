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
auto Scene::IsIntersect
(
 const Ray& ray,
 Intersection* intersection
)
  const noexcept -> bool
{
  intersection->SetDistance (kInfinity);
  intersection->SetShape (nullptr);
  intersection->SetMaterial (nullptr);

  for (const auto& primitive : primitives_)
  {
    // Intersection test.
    Intersection temp;
    // temp.SetDistance (kInfinity);
    // temp.SetShape (nullptr);
    // temp.SetMaterial (nullptr);
    if (primitive->IsIntersect (ray, &temp))
    {
      if (temp.Distance () < intersection->Distance ())
      {
        *intersection = temp;
      }
    }
  }
  return static_cast <bool> (*intersection);
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
