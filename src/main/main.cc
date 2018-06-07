/*
// ---------------------------------------------------------------------------
*/
#include "../core/niepce.h"
#include "../core/render_settings.h"
#include "../renderer/path_tracer.h"
#include "../random/xorshift.h"
#include "../core/bounds2f.h"
#include "../core/image.h"
#include "../core/imageio.h"
#include "../core/stop_watch.h"
#include "../texture/image_texture.h"
#include "../core/utilities.h"
#include "../bsdf/microfacet_reflection.h"
#include "../material/metal.h"
#include "../core/transform.h"
#include "../camera/realistic_camera.h"
#include "../sampler/low_discrepancy_sequence.h"
#include "../core/transform.h"
#include "../core/thread_pool.h"
#include "../core/singleton.h"
/*
// ---------------------------------------------------------------------------
*/
INITIALIZE_EASYLOGGINGPP
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
auto Initialize () -> void
{
  auto& stop_watch = Singleton<StopWatch>::Instance ();
  stop_watch.Start ();
}
/*
// ---------------------------------------------------------------------------
*/
auto Finalize () -> void
{
  auto& stop_watch = Singleton<StopWatch>::Instance ();
  auto time = stop_watch.Stop ();
  std::cout << time.ToString () << std::endl;

  SingletonFinalizer::Finalize ();
}
/*
// ---------------------------------------------------------------------------
*/
auto RenderScene () -> void
{
  niepce::Transform t = LookAt (Point3f  (50, 50, 550),
                                Point3f  (50, 50,   0),
                                Vector3f ( 0,  1,   0));
  std::shared_ptr<RealisticCamera> camera (new RealisticCamera(t,
                                                      "result.ppm",
                                                      360,
                                                      240,
                                                      43.2666153056, // Full size sensor size
                                                      "../assets/lenses/thin.dat",
                                                      1.0,
                                                      5.5,
                                                      false));
  CameraSample cs (Point2f (100, 100), Point2f (0.355, 0.089));
  Ray ray;
  camera->GenerateRay (cs, &ray);
  std::cout << ray.ToString() << std::endl;

  // niepce::Scene scene;
  // scene.ReadyCornellBox ();
  // PathTracer pt (camera, scene);
  // pt.Render ();
}
/*
// ---------------------------------------------------------------------------
*/
} // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
int main (int argc, char* argv[])
{
  niepce::Initialize ();
  niepce::RenderScene ();
  niepce::Finalize ();
  return 0;
}
