#include "../core/niepce.h"
#include "../core/transform.h"
#include "../camera/camera.h"
#include "../sampler/random_sampler.h"
#include "../scene/scene.h"
#include "../scene/scene_utils.h"
#include "../shape/sphere.h"
#include "../integrator/path_tracer.h"
#include "../integrator/debug.h"
/*
// ---------------------------------------------------------------------------
*/
auto main(int argc, char *argv[]) -> int
{
  using namespace niepce;

  // std::pair<std::shared_ptr<Camera>, Scene> render_scene = CreateCornellBox ();
  // std::pair<std::shared_ptr<Camera>, Scene> render_scene = SphereAndPlane();
  // std::pair<std::shared_ptr<Camera>, Scene> render_scene = CreateComparisonSphereScene();
  std::pair<std::shared_ptr<Camera>, Scene> render_scene = CreateSphereScene ();
  // std::pair<std::shared_ptr<Camera>, Scene> render_scene = CreateSphereCornellBox ();

  std::cout << "Render" << std::endl;

  const std::shared_ptr<Camera> camera (render_scene.first);
  const Scene scene (render_scene.second);
  const std::shared_ptr<Sampler> sampler (new RandomSampler ());

  std::unique_ptr<Integrator> pt (new PathTracer (camera, sampler, 15));
  pt->Render (scene);

  std::unique_ptr<Integrator> debug (new DebugIntegrator (camera, sampler));
  debug->Render (scene);

  return 0;
}
