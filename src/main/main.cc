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
#include "../sampler/low_discrepancy_sequence.h"
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
  niepce::Bounds2f b;
  std::cout << b.ToString () << std::endl;


  // niepce::StopWatch stopwatch;
  // stopwatch.Start ();
  // niepce::RenderScene ();
  // stopwatch.Stop ();
  // std::cout << std::endl;

  return 0;
}
