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
#include "../texture/value_texture.h"
#include "../scene/scene_importer.h"
#include "../core/attributes.h"
#include "../bsdf/bsdf_record.h"
#include "../bsdf/bsdf.h"
#include "../bsdf/bxdf.h"
#include "../sampler/low_discrepancy_sequence.h"
#include "../sampler/random_sampler.h"
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
  auto& stop_watch = Singleton <StopWatch>::Instance ();
  stop_watch.Start ();
}
/*
// ---------------------------------------------------------------------------
*/
auto Finalize () -> void
{
  auto& stop_watch = Singleton <StopWatch>::Instance ();
  auto time = stop_watch.Stop ();
  std::cout << time.ToString () << std::endl;
  SingletonFinalizer::Finalize ();
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
  niepce::SceneImporter importer (argv[1]);
  auto settings = importer.ExtractRenderSettings ();
  auto scene    = importer.ExtractScene ();
  auto camera   = importer.ExtractCamera ();
  std::cout << "Start rendering" << std::endl;
  niepce::PathTracer pt (settings, scene, camera);
  pt.Render ();
  niepce::Finalize ();

  return 0;
}
