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
  settings.AddItem (RenderSettings::Item::kWidth,  960);
  settings.AddItem (RenderSettings::Item::kHeight, 540);
  settings.AddItem (RenderSettings::Item::kTileWidth,  128);
  settings.AddItem (RenderSettings::Item::kTileHeight, 90);
  settings.AddItem (RenderSettings::Item::kNumThread,
                    std::thread::hardware_concurrency ());
  settings.AddItem (RenderSettings::Item::kNumSamples, 32);
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
  niepce::RenderScene ();
  stopwatch.Stop ();

  return 0;

  niepce::Vector3f n, s, t;
  n = niepce::Vector3f (1, 1, 0);
  n.Normalize ();
  niepce::BuildOrthonormalBasis(n, &s, &t);
  std::cout << "Normalized n : ";
  std::cout << n.X () << " " << n.Y () << " " << n.Z () << std::endl;

  niepce::Vector3f in (-1, -1, 0);
  in.Normalize();
  std::cout << "Input in world : ";
  std::cout << in.X () << " " << in.Y () << " " << in.Z () << std::endl;

  // to bsdf coordinates
  niepce::Vector3f local (Dot (in, t), Dot (in, n), Dot (in, s));

  std::cout << "Vector in bsdf coordinates : ";
  std::cout << local.X () << " " << local.Y () << " " << local.Z () << std::endl;

  // to world
  niepce::Vector3f world
    = niepce::Vector3f (local.X () * t.X () + local.Y () * n.X () + local.Z () * s.X (),
                        local.X () * t.Y () + local.Y () * n.Y () + local.Z () * s.Y (),
                        local.X () * t.Z () + local.Y () * n.Z () + local.Z () * s.Z ());
  std::cout << "vector in world coordinates : ";
  std::cout << world.X () << " " << world.Y () << " " << world.Z () << std::endl;


  return 0;
}
