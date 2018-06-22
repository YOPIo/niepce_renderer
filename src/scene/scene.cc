/*!
 * @file scene.cc
 * @brief 
 * @author Masashi Yoshida
 * @date 2018/5/5
 * @details 
 */
#include "scene.h"
#include "../accelerator/bvh.h"
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
  primitives_ (primitives),
  original_   (primitives)
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
  /*
  bool hit = false;
  Intersection tmp;
  for (const auto& p : original_)
  {
    if (p->IsIntersect (ray, &tmp))
    {
      if (tmp.Distance () < intersection->Distance ())
      {
        hit = true;
        *intersection = tmp;
      }
    }
  }
  return hit;
  */

  return primitives_.IsIntersect (ray, intersection);
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
