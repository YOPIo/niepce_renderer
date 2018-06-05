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
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
auto Initialize () -> void
{}
/*
// ---------------------------------------------------------------------------
*/
auto Finalize () -> void
{
  SingletonFinalizer::Finalize ();
}
/*
// ---------------------------------------------------------------------------
*/
auto RenderScene () -> void
{
  niepce::Transform t;
  std::shared_ptr<Camera> camera (new RealisticCamera(t,
                                                      "result.ppm",
                                                      256,
                                                      256,
                                                      3.5,
                                                      "../assets/lenses/wide.22mm.dat",
                                                      0.5,
                                                      1,
                                                      false));

  // camera->Dump();
  // camera->RenderExitPupil (niepce::Point2f (0, 0), "aperture.ppm");

  niepce::Scene scene;
  scene.ReadyCornellBox ();
  PathTracer pt (camera, scene);
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
  niepce::Initialize ();
  niepce::StopWatch stopwatch;
  stopwatch.Start ();
  niepce::RenderScene ();
  stopwatch.Stop ();
  niepce::Finalize ();

  return 0;

  niepce::Film f ("", 480, 480, 35.0);
  niepce::FilmTile ft (niepce::Bounds2f (niepce::Point2f (32, 32),
                                         niepce::Point2f (100, 400)));

  auto func = [&] (int x, int y) -> void
  {
    ft.SetValueAt (x, y, niepce::Spectrum(0.75, 0.25, 0.25));
  };
  BoundFor2 (func, niepce::Bounds2f (ft.Width(), ft.Height()));
  f.AddFilmTile(ft);

  f.SaveAs ("aaa.ppm");

  return 0;
}
