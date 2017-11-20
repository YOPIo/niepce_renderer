#include "../core/niepce.h"
#include "../camera/camera.h"
#include "../scene/scene.h"
#include "../scene/scene_creator.h"
#include "../sampler/random_sampler.h"
#include "../integrator/path_tracer.h"
/*
// ---------------------------------------------------------------------------
*/
auto main(int argc, char *argv[]) -> int
{
  std::pair <std::shared_ptr<niepce::Camera>, std::shared_ptr<niepce::Scene>> pair;
  niepce::SamplerPtr sampler (niepce::CreateRandomSampler ());
  pair = niepce::CreateCornellBox ();

  std::cout << "Rendering begin. " << std::endl;
  std::shared_ptr<niepce::PathTracer> path (new niepce::PathTracer (pair.first, sampler, 8));
  path->Render (*pair.second);

  return 0;
}
