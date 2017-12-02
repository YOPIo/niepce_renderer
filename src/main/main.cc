#include "../core/niepce.h"
#include "../camera/camera.h"
#include "../core/image.h"
#include "../scene/scene.h"
#include "../scene/scene_creator.h"
#include "../sampler/random_sampler.h"
#include "../integrator/path_tracer.h"
#include "../integrator/debug.h"
#include "../filter/filter.h"
/*
// ---------------------------------------------------------------------------
*/
using namespace niepce;
/*
// ---------------------------------------------------------------------------
*/
auto main(int argc, char *argv[]) -> int
{
  std::pair <std::shared_ptr<niepce::Camera>, std::shared_ptr<niepce::Scene>> pair;
  niepce::SamplerPtr sampler (niepce::CreateRandomSampler ());
  // pair = niepce::CreateCornellBox ();
  pair = niepce::CreateSphereScene ();

  std::shared_ptr <niepce::PathTracer> path (new niepce::PathTracer (pair.first, sampler, 8));
  std::shared_ptr <niepce::DebugIntegrator> debug (new niepce::DebugIntegrator (pair.first, sampler));
  path->Render (*pair.second);
  debug->Render (*pair.second);

  /*
  // Filter test
  niepce::ImagePtr <niepce::Float> img (niepce::LoadImage <niepce::Float> ("./cornell_box.png"));
  niepce::ImagePtr <niepce::Float> res = niepce::NonLocalMeansFilter (img, 0.1, 0.1);
  niepce::SaveAs ("after.png", *res);
  */


  Normal3f n(0, 0, 1);
  Vector3f u, v;
  OrthoNormalBasis(n, &u, &v);
  std::cout << "local x: " << u << std::endl;
  std::cout << "local y: " << v << std::endl;

  Transform transform (u.x, v.x, n.x, 0.0,
                       u.y, v.y, n.y, 0.0,
                       u.z, v.z, n.z, 0.0,
                       0.0, 0.0, 0.0, 1.0);

  Vector3f in_world (-1, 0, -1);

  Vector3f in_local = transform * in_world;

  std::cout << in_local << std::endl;

  std::cout << transform.GetInvMatrix() << std::endl;

  return 0;
}
