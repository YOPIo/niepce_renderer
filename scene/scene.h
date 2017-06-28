#ifndef _SCENE_H_
#define _SCENE_H_

#include "../accelerators/bvh.h"
#include "../cameras/camera.h"
#include "../core/niepce.h"
#include "../core/settings.h"
#include "../geometries/ray.h"
#include "../shapes/shape.h"
#include "../shapes/triangle.h"
#include "../shapes/triangle_mesh.h"
#include "../primitives/primitive.h"
#include "../primitives/geometric_primitive.h"
#include "../materials/material.h"

namespace niepce
{


class Scene
{
  /* Scene constructors */
 public:
  Scene ();
  Scene (const char* filename);
  virtual ~Scene ();

  Scene (const Scene&  scene) = default;
  Scene (      Scene&& scene) = default;

  /* Scene operators*/
  auto operator = (const Scene& scene) -> Scene& = default;
  auto operator = (Scene&& scene)      -> Scene& = default;


  /* Scene public methods */
 public:
  // TODO: Implementation
  // Load scene file and build BVH or Kdtree data structure
  auto LoadScene (const char* filename) -> void = delete;

  // Destroy a scene if scene has already loaded and create cornell box scene
  // then construct a BVH or Kdtree data structure
  auto MakeCornellBox () -> void;

  // Return render setting information
  auto GetSettings () const -> Settings;

  // Ray-object intersection test
  auto IsIntersect (const Ray& ray, Interaction* interaction) -> bool;


  /* Scene private methods */
 private:
  // Construct a BVH or Kdtree
  auto Construct (const std::vector<std::shared_ptr<Primitive>>& primitives) -> void;

  // Make primitives from meshes and materials
  auto MakePrimitives (const std::shared_ptr<TriangleMesh>&          mesh,
                       const std::vector<std::shared_ptr<Material>>& materials)
  -> std::vector<std::shared_ptr<Primitive>>;


  /* Scene private data */
 private:
  std::shared_ptr<Primitive> root_;     // Root node of BVH
  Settings                   settings_; // Render settings ([width, height], threads etc...)
}; // class Scene


}  // namespace niepce

#endif // _SCENE_H_
