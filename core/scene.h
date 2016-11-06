#ifndef _SCENE_H_
#define _SCENE_H_

#include <memory>
#include <vector>

#include "../core/common.h"
#include "../geometry/geometry.h"
#include "../geometry/face.h"

namespace niepce
{

class Scene
{
 public:
  Scene();
  virtual ~Scene();

  Scene(const Scene& Name) = default;
  Scene(Scene&& Name)      = default;
  Scene& operator = (const Scene& Name) = default;
  Scene& operator = (Scene&& Name)      = default;

  auto Intersect(const Ray& ray, HitRecord* hit_record) -> Face*;

  auto Append(const Face& face) -> void;
  auto Append(Face&& face) -> void;
  auto Size() -> std::size_t;

 private:
  std::vector<Face> scene_;
};

} // namespace niepce

#endif // _SCENE_H_
