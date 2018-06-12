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
#include "../core/bounds3f.h"
#include "../core/singleton.h"
#include "../core/memory.h"
#include "../camera/pinhole.h"
#include "../texture/bool_texture.h"
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
  niepce::Transform t = LookAt (Point3f  (50, 50, 200),
                                Point3f  (50, 50,   0),
                                Vector3f ( 0,  1,   0));
  std::shared_ptr <Camera> camera (new PinholeCamera (t,
                                                      90,  // fov
                                                      10,  // [mm]
                                                      100, // [m]
                                                      "result.ppm",
                                                      360 * 3,
                                                      240 * 3,
                                                      43.2666153056));
  niepce::Scene scene;
  scene.ReadyCornellBox ();
  PathTracer pt (camera, scene);
  pt.Render ();
}
/*
// ---------------------------------------------------------------------------
*/
auto BokehTest () -> void
{
  Transform t = LookAt (Point3f  (80, 80, -20),
                        Point3f  (20, 20,  20),
                        Vector3f ( 0,  1,   0));
  std::shared_ptr <Camera> camera (new PinholeCamera (t,
                                                      90,  // fov
                                                      50,  // [mm]
                                                      100, // [m]
                                                      "result.ppm",
                                                      360,
                                                      240,
                                                      43.2666153056));
  Scene scene;
  scene.BuildBokehScene ();
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
  // niepce::RenderScene ();
  // niepce::BokehTest ();
  niepce::Finalize ();

  niepce::ImageIO<bool> tex ("/home/yopio/workspace/niepce/assets/aperture.png");
  // tex.SaveAs ("bool_heart.ppm");
  return 0;
}
