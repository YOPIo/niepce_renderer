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
  niepce::Normalize (niepce::Vector3f (-1, -1, -1));
  niepce::Intersection intersection;
  intersection.SetPosition (niepce::Point3f (0, 0, 0));
  intersection.SetNormal   (niepce::Vector3f (0, 1, 0));

  niepce::BeckmannDistribution distribution (0.5, 0.5, false);
  niepce::FresnelDielectric    fresnel (1.0, 1.35);
  niepce::MicrofacetReflection microfacet (intersection,
                                           niepce::Spectrum (0.7),
                                           &distribution,
                                           &fresnel);

  const niepce::Vector3f outgoing (-1, -1, -1);

  const niepce::Vector3f wh =
    distribution.SampleMicrofacetNormal(outgoing,
                                        niepce::Point2f (0.1411, 0.009825));

  std::cerr << "Microfacet normal" << std::endl;
  std::cerr << wh.X () << ", " << wh.Y () << ", " << wh.Z () << std::endl;

  const niepce::Vector3f incident = niepce::bsdf::Reflect (outgoing, wh);

  std::cerr << "Sampled direction." << std::endl;
  std::cerr << incident.X () << ", "
            << incident.Y () << ", "
            s<
    < incident.Z () << std::endl;

  return 0;
}
