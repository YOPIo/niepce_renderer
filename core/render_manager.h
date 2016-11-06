#ifndef _RENDER_MANAGER_H_
#define _RENDER_MANAGER_H_

#include <string>
#include <vector>
#include <memory>

#include "../core/common.h"
#include "../core/scene.h"
#include "../camera/pinhole_camera.h"
#include "../image/film.h"
#include "../geometry/geometry_common.h"
#include "../material/material.h"
#include "../material/lambert.h"
#include "../material/phong.h"
#include "../material/light.h"

namespace niepce
{

class RenderManager
{
  using Cam = std::unique_ptr<Camera>;

 public:
  RenderManager();
  ~RenderManager();

  RenderManager(const RenderManager& manager) = delete;
  RenderManager(RenderManager&& manager)      = delete;
  RenderManager& operator = (const RenderManager& manager) = delete;
  RenderManager& operator = (RenderManager&& manager)      = delete;

  auto Render(const Size& size,
              int num_sample, int num_super_sample) -> void;
  auto LoadScene(const char* filename) -> void;

  auto RenderCornellBox(const char* filename,
                        const Size& size,
                        int num_sample,
                        int num_super_sample) -> void;

 private:
  auto Radiance(const Ray& ray,
                int        depth,
                Random&    random) -> glm::vec3;
  auto BuildCornellBoxScene() -> void;
  auto SetupCameraForCornellBox() -> void;
  auto InitializeFilm(const Size& size) -> void;
  auto SaveAs(const char* filename) -> void;

 private:
  Scene scene_;
  Cam   camera_;
  Film  film_;
};

} // namespace niepce

#endif // _RENDER_MANAGER_H_
