/*
// ---------------------------------------------------------------------------
*/
#include "../core/niepce.h"
#include "../core/render_settings.h"
#include "../renderer/path_tracer.h"
#include "../random/xorshift.h"
#include "../math/vector3f.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
Scene scene;
/*
// ---------------------------------------------------------------------------
*/
auto BuildScene () -> void
{
  std::shared_ptr <Material> white (new Material ());
  white->color    = Vector3f (0.75, 0.75, 0.75);
  white->emittion = Vector3f::Zero ();
  white->type_    = Material::kDiffuse;

  std::shared_ptr <Material> red   (new Material ());
  red->color    = Vector3f (0.75, 0.25, 0.25);
  red->emittion = Vector3f::Zero ();
  red->type_    = Material::kDiffuse;

  std::shared_ptr <Material> blue  (new Material ());
  blue->color    = Vector3f (0.25, 0.25, 0.75);
  blue->emittion = Vector3f::Zero ();
  blue->type_    = Material::kDiffuse;

  std::shared_ptr <Material> mirror (new Material ());
  mirror->color    = Vector3f (0.999, 0.999, 0.999);
  mirror->emittion = Vector3f::Zero ();
  mirror->type_    = Material::kSpecular;

  std::shared_ptr <Material> glass (new Material ());
  glass->color    = Vector3f (0.999, 0.999, 0.999);
  glass->emittion = Vector3f::Zero ();
  glass->type_    = Material::kSpecular;

  std::shared_ptr <Material> light (new Material ());
  light->color    = Vector3f::Zero ();
  light->emittion = Vector3f (12, 12, 12);
  light->type_    = Material::kRefraction;

  // Position, radius
  auto left   = CreateSphere (Point3f (1e5 + 1, 40.8, 81.6), 1e5);
  auto right  = CreateSphere (Point3f (-1e5 + 99, 40.8, 81.6), 1e5);
  auto back   = CreateSphere (Point3f (50, 40.8, 1e5), 1e5);
  auto front  = CreateSphere (Point3f (50, 40.8, -1e5 + 170), 1e5);
  auto bottom = CreateSphere (Point3f (50, 1e5, 81.6), 1e5);
  auto top    = CreateSphere (Point3f (50, -1e5 + 81.6, 81.6), 1e5);
  auto mirr   = CreateSphere (Point3f (27, 16.5, 47), 16.5);
  auto glas   = CreateSphere (Point3f (73, 16.5, 78), 16.5);
  auto lite   = CreateSphere (Point3f (50, 681.6 - 0.27, 81.6), 600);

  scene.AddPrimitive (CreatePrimitive (mirr, white));
  // Primitive
  scene.AddPrimitive (CreatePrimitive (left,   red));
  scene.AddPrimitive (CreatePrimitive (right,  blue));
  scene.AddPrimitive (CreatePrimitive (back,   white));
  scene.AddPrimitive (CreatePrimitive (front,  white));
  scene.AddPrimitive (CreatePrimitive (bottom, white));
  scene.AddPrimitive (CreatePrimitive (top,    white));
  scene.AddPrimitive (CreatePrimitive (mirr,   mirror));
  scene.AddPrimitive (CreatePrimitive (glas,   glass));
  scene.AddPrimitive (CreatePrimitive (lite,   light));
}
/*
// ---------------------------------------------------------------------------
*/
auto RenderScene () -> void
{
  RenderSettings settings;
  settings.AddItem (RenderSettings::Item::kWidth,  1024 / 2);
  settings.AddItem (RenderSettings::Item::kHeight, 768 / 2);
  settings.AddItem (RenderSettings::Item::kTileWidth,  128);
  settings.AddItem (RenderSettings::Item::kTileHeight, 96);
  settings.AddItem (RenderSettings::Item::kNumThread,
                    std::thread::hardware_concurrency ());
  settings.AddItem (RenderSettings::Item::kNumSamples, 4);
  settings.AddItem (RenderSettings::Item::kPTMaxDepth, 5);

  PathTracer pt (settings);
  pt.Render (scene);
}
/*
// ---------------------------------------------------------------------------
*/
} // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
using namespace niepce;
/*
// ---------------------------------------------------------------------------
*/
int main (int argc, char* argv[])
{

  niepce::BuildScene ();
  niepce::RenderScene ();

  /*
  Ray ray (Point3f (10, 0, 0), Vector3f (0, 0, 1).Normalize ());

  Scene scene;
  auto mat   = std::make_shared <Material> ();
  auto shape = CreateSphere (Point3f (9, 0, 10), 1);
  auto prim  = CreatePrimitive (shape, mat);

  scene.AddPrimitive (prim);

  Intersection intersection;
  scene.IsIntersect(ray, &intersection);

  if (intersection) { std::cout << "hit" << std::endl; }
  else { std::cout << "no hit" << std::endl; }
  */

  return 0;
}
