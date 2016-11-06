#include "scene.h"

namespace niepce
{
Scene::Scene()
{}

Scene::~Scene()
{}

auto Scene::Intersect(const Ray& ray, HitRecord* hit_record) -> Face*
{
  Face* face = nullptr;
  for (auto& obj : scene_)
  {
    HitRecord buff = HitRecord();
    if (obj.IsIntersect(ray, &buff))
    {
      if (buff.distance_ < hit_record->distance_)
      {
        *hit_record = buff;
        face = &obj;
      }
    }
  }
  return face;
}

auto Scene::Append(const Face& face) -> void
{
  scene_.push_back(face);
}

auto Scene::Append(Face&& face) -> void
{
  scene_.push_back( std::move(face) );
}

auto Scene::Size() -> std::size_t
{
  return scene_.size();
}

} // namespace niepce
