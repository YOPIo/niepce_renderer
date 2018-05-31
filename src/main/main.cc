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
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
auto RenderScene () -> void
{
  RenderSettings settings;
  settings.AddItem (RenderSettings::Item::kWidth,  960 / 2);
  settings.AddItem (RenderSettings::Item::kHeight, 540 / 2);
  settings.AddItem (RenderSettings::Item::kTileWidth,  128 / 2);
  settings.AddItem (RenderSettings::Item::kTileHeight,  90 / 2);
  settings.AddItem (RenderSettings::Item::kNumThread,
                    std::thread::hardware_concurrency ());
  settings.AddItem (RenderSettings::Item::kNumSamples, 8);
  settings.AddItem (RenderSettings::Item::kPTMaxDepth, 5);

  niepce::Scene scene;
  scene.ReadyCornellBox ();

  PathTracer pt (scene,settings);
  pt.Render ();
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
  // niepce::StopWatch stopwatch;
  // nstopwatch.Start ();
  // niepce::RenderScene ();
  // stopwatch.Stop ();

  niepce::Transform t;

  niepce::RealisticCamera camera (t,
                                  "../assets/lenses/wide.22mm.dat",
                                  3.0,
                                  3.0,
                                  false);
  // camera.RenderExitPupil (niepce::Point2f (0, 0), "aperture.ppm");

  niepce::Transform c2w = niepce::LookAt (niepce::Point3f  (5, 5, 5),
                                          niepce::Point3f  (5, 5, 0),
                                          niepce::Vector3f (0, 1, 0));
  niepce::Ray camera_ray (niepce::Point3f (0, 0, 0), niepce::Vector3f (0, 0, 1));

  std::cout << camera_ray.ToString() << std::endl;
  std::cout << (c2w * camera_ray).ToString() << std::endl;

  return 0;
}
