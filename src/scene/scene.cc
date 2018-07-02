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
Scene::Scene
(
 const std::vector <std::shared_ptr <Primitive>>& primitives,
 const std::vector <std::shared_ptr <Light>>&     lights,
 const std::shared_ptr <niepce::InfiniteLight>&   inf_light
) :
  primitives_ (primitives),
  lights_     (lights),
  // original_   (primitives)
  infinite_light_ (inf_light)
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
auto Scene::InfiniteLight ()
  const noexcept -> std::shared_ptr <niepce::InfiniteLight>
{
  if (infinite_light_)
  {
    return infinite_light_;
  }
  return nullptr;
}
/*
// ---------------------------------------------------------------------------
*/
auto CreateScene
(
 const std::vector <std::shared_ptr <Primitive>>& primitives,
 const std::vector <std::shared_ptr <Light>>&     lights,
 const std::shared_ptr <niepce::InfiniteLight>&   inf_light
)
  -> Scene*
{
  return new Scene (primitives, lights, inf_light);
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
