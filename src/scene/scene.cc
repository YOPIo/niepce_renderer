/*!
 * @file scene.cc
 * @brief 
 * @author Masashi Yoshida
 * @date 2018/5/5
 * @details 
 */
#include "scene.h"
#include "../material/matte.h"
#include "../material/metal.h"
#include "../shape/triangle.h"
#include "../texture/image_texture.h"
#include "../texture/value_texture.h"
#include "../accelerator/aggregation.h"
#include "../primitive/primitive.h"
#include "../sampler/random_sampler.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
Scene::Scene (const std::vector <std::shared_ptr <Primitive>>& primitives) :
  primitives_ (primitives)
{}
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
  for (const auto& primitive : primitives_)
  {
    // Intersection test
    Intersection tmp;
    if (primitive->IsIntersect (ray, &tmp))
    {
      if (tmp.Distance () < intersection->Distance ())
      {
        *intersection = tmp;
        intersection->MakeHitFlagTrue ();
      }
    }
  }
  return static_cast <bool> (*intersection);
}
/*
// ---------------------------------------------------------------------------
*/
auto CreateScene (const std::vector <std::shared_ptr <Primitive>>& primitives)
  -> Scene*
{
  return new Scene (primitives);
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
