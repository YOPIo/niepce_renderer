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
#include "../bsdf/microfacet_reflection_pbrt.h"
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
} // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
int main (int argc, char* argv[])
{
  using Spectrum = niepce::Spectrum;

  niepce::Point2f sample (0.1352134, 0.7291491);
  niepce::Vector3f in (1, 0, -1);
  in.Normalize ();
  niepce::Vector3f n (0, 0, 1);

  // ---------------------------------------------------------------------------
  // niepce
  // ---------------------------------------------------------------------------
  auto i = niepce::Intersection ();
  i.SetPosition (niepce::Point3f (0, 0, 0));
  i.SetNormal (n);
  i.SetOutgoing (-in);

  auto nf = new niepce::FresnelConductor (Spectrum (1.0),
                                         Spectrum (1.5),
                                         Spectrum (0.3, 0.3, 0.45));
  auto nd = new niepce::TrowbridgeReitz (0.5, 0.5, false);
  auto nm = niepce::MicrofacetReflection (i, Spectrum (1.0), nd, nf);

  niepce::BsdfRecord record (i);
  auto no = nm.Sample (&record, sample);

  // ---------------------------------------------------------------------------
  // pbrt
  // ---------------------------------------------------------------------------
  auto pf = new pbrt::FresnelConductor (Spectrum (1.0),
                                        Spectrum (1.5),
                                        Spectrum (0.3, 0.3, 0.45));
  auto pd = new pbrt::TrowbridgeReitzDistribution (0.5, 0.5, false);
  auto pm = pbrt::MicrofacetReflection (Spectrum (1.0), pd, pf);

  niepce::Vector3f wi;
  niepce::Float pdf;
  pbrt::BxDFType type;
  auto po = pm.Sample_f (-in, &wi, sample, &pdf, &type);

  // return 0;

  /*
  // ---------------------------------------------------------------------------
  */


  if (argc != 2)
  {
    std::cout << "Input filename." << std::endl;
    return 0;
  }
  std::cout << "the number of avaliable threads : "
	    << std::thread::hardware_concurrency () << std::endl;
  niepce::Initialize ();
  niepce::SceneImporter importer (argv[1]);
  auto scene  = importer.ExtractScene ();
  auto camera = importer.ExtractCamera ();
  niepce::PathTracer pt (scene, camera);
  pt.Render ();
  niepce::Finalize ();

  return 0;
}
