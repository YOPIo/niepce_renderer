/*
// ---------------------------------------------------------------------------
*/
#include "../core/niepce.h"
#include "../core/render_settings.h"
#include "../renderer/path_tracer.h"
#include "../random/xorshift.h"
#include "../core/bounds2f.h"
#include "../core/image.h"
#include "../core/ioimage.h"
#include "../core/stop_watch.h"
#include "../texture/image_texture.h"
#include "../core/utilities.h"
#include "../bsdf/microfacet_reflection.h"
#include "../material/metal.h"
#include "../core/transform.h"
#include "../camera/realistic_camera.h"
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
  niepce::StopWatch stopwatch;
  stopwatch.Start ();
  // niepce::RenderScene ();
  stopwatch.Stop ();
  std::cout << std::endl;

  niepce::Transform t;
  /*
  niepce::RealisticCamera camera (t,
                                  "../assets/lenses/wide.22mm.dat",
                                  1.0,
                                  16.0,
                                  true);
  */
  niepce::RealisticCamera camera (t,
                                  "../assets/lenses/dgauss.50mm.dat",
                                  1.0,
                                  16.0,
                                  true);

  // camera.DrawLensSystem ("../tools/test.plt");

  niepce::Ray in = niepce::Ray (niepce::Point3f  (0.005, 0, -1),
                                niepce::Vector3f (0, 0, 1));
  niepce::Ray out;
  if (camera.CanRayThroughLensSystemFromFilm (in, &out))
  {
    std::cout << "throught" << std::endl;
  }

  return 0;

  std::array <niepce::Float, 2> fz, pz;
  camera.ComputeThickLensApproximation (&fz, &pz);

  std::cout << "\nFrom Scene side tracing :\n";
  std::cout << "Focus point     : " << fz[0] << std::endl;
  std::cout << "Principal plame : " << pz[0] << std::endl;

  std::cout << "\nFrom Film side tracing :\n";
  std::cout << "Focus point     : " << fz[1] << std::endl;
  std::cout << "Principal plame : " << pz[1] << std::endl;

  return 0;
}
