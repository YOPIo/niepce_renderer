/*!
 * @file scene.cc
 * @brief 
 * @author Masashi Yoshida
 * @date 2018/5/5
 * @details 
 */
#include "scene.h"
#include "../material/matte.h"
#include "../material/metal.h"
#include "../shape/triangle.h"
#include "../texture/image_texture.h"
#include "../texture/value_texture.h"
#include "../accelerator/aggregation.h"
#include "../primitive/primitive.h"
#include "../sampler/random_sampler.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
auto Scene::IsIntersect
(
 const Ray& ray,
 Intersection* intersection
)
  const noexcept -> bool
{
  for (const auto& primitive : primitives_)
  {
    // Intersection test
    Intersection tmp;
    if (primitive->IsIntersect (ray, &tmp))
    {
      if (tmp.Distance () < intersection->Distance ())
      {
        *intersection = tmp;
        intersection->MakeHitFlagTrue ();
      }
    }
  }
  return static_cast <bool> (*intersection);
}
/*
// ---------------------------------------------------------------------------
*/
auto Scene::ReadyCornellBox () -> void
{
  // Generate textures.
  std::shared_ptr <Texture> white = CreateValueTexture (Vector3f (0.75));
  std::shared_ptr <Texture> red
    = CreateValueTexture (Vector3f (0.75, 0.25, 0.25));
  std::shared_ptr <Texture> green
    = CreateValueTexture (Vector3f (0.25, 0.75, 0.25));
  std::shared_ptr <Texture> black
    = CreateValueTexture (Vector3f::Zero ());
  std::shared_ptr <Texture> light = CreateValueTexture (Vector3f (12, 12, 12));
  std::shared_ptr <Texture> tex = CreateImageTexture ("/home/yopio/workspace/niepce/assets/icon.png");

  // Generate materials.
  std::shared_ptr <Material> matte_white (new Matte (white, nullptr));
  std::shared_ptr <Material> matte_red   (new Matte (red,   nullptr));
  std::shared_ptr <Material> matte_green (new Matte (green, nullptr));
  std::shared_ptr <Material> matte_light (new Matte (black, light));
  std::shared_ptr <Material> matte_tex   (new Matte (tex,   nullptr));

  // Vertex positions
  std::vector <Point3f> positions = { Point3f (  0.0f,   0.0f,   0.0f),
                                      Point3f (100.0f,   0.0f,   0.0f),
                                      Point3f (  0.0f,   0.0f, 100.0f),
                                      Point3f (100.0f,   0.0f, 100.0f),
                                      Point3f (  0.0f, 100.0f,   0.0f),
                                      Point3f (100.0f, 100.0f,   0.0f),
                                      Point3f (  0.0f, 100.0f, 100.0f),
                                      Point3f (100.0f, 100.0f, 100.0f),
                                      Point3f ( 25.0f,  99.5f,  25.0f),
                                      Point3f ( 75.0f,  99.5f,  25.0f),
                                      Point3f ( 25.0f,  99.5f,  75.0f),
                                      Point3f ( 75.0f,  99.5f,  75.0f),};
  // Texture coordinates
  std::vector <Point2f> uvs = {Point2f (0.0f, 0.0f),
                               Point2f (1.0f, 0.0f),
                               Point2f (0.0f, 1.0f),
                               Point2f (1.0f, 1.0f)};

  // Create triangle mesh
  std::shared_ptr <TriangleMesh> mesh (new TriangleMesh (positions, {}, uvs));

  // Generate triangles
  std::array <std::shared_ptr <Triangle>, 12> triangles;
  triangles[0] = std::shared_ptr <Triangle> (new Triangle (mesh,
                                                           {0, 2, 1},
                                                           {0, 0, 0},
                                                           {0, 0, 0},
                                                           true));
  triangles[1] = std::shared_ptr <Triangle> (new Triangle (mesh,
                                                           {1, 2, 3},
                                                           {0, 0, 0},
                                                           {0, 0, 0},
                                                           true));
  triangles[2] = std::shared_ptr <Triangle> (new Triangle (mesh,
                                                           {4, 5, 6},
                                                           {0, 0, 0},
                                                           {0, 0, 0},
                                                           true));
  triangles[3] = std::shared_ptr <Triangle> (new Triangle (mesh,
                                                           {5, 7, 6},
                                                           {0, 0, 0},
                                                           {0, 0, 0},
                                                           true));
  triangles[4] = std::shared_ptr <Triangle> (new Triangle (mesh,
                                                           {1, 3, 5},
                                                           {0, 0, 0},
                                                           {0, 0, 0},
                                                           true));
  triangles[5] = std::shared_ptr <Triangle> (new Triangle (mesh,
                                                           {3, 7, 5},
                                                           {0, 0, 0},
                                                           {0, 0, 0},
                                                           true));
  triangles[6] = std::shared_ptr <Triangle> (new Triangle (mesh,
                                                           {0, 4, 6},
                                                           {0, 0, 0},
                                                           {0, 0, 0},
                                                           true));
  triangles[7] = std::shared_ptr <Triangle> (new Triangle (mesh,
                                                           {0, 6, 2},
                                                           {0, 0, 0},
                                                           {0, 0, 0},
                                                           true));
  triangles[8] = std::shared_ptr <Triangle> (new Triangle (mesh,
                                                           {0, 1, 5},
                                                           {0, 0, 0},
                                                           {2, 3, 1},
                                                          true));
  triangles[9] = std::shared_ptr <Triangle> (new Triangle (mesh,
                                                           {0, 5, 4},
                                                           {0, 0, 0},
                                                           {2, 1, 0},
                                                           true));
  triangles[10] = std::shared_ptr <Triangle> (new Triangle (mesh,
                                                            {8, 9, 10},
                                                            {0, 0, 0},
                                                            {0, 0, 0},
                                                            true));
  triangles[11] = std::shared_ptr <Triangle> (new Triangle (mesh,
                                                            {9, 11, 10},
                                                            {0, 0, 0},
                                                            {0, 0, 0},
                                                            true));

  // Bottom
  primitives_.push_back (CreatePrimitive (triangles[0], matte_white));
  primitives_.push_back (CreatePrimitive (triangles[1], matte_white));
  // Top
  primitives_.push_back (CreatePrimitive (triangles[2], matte_white));
  primitives_.push_back (CreatePrimitive (triangles[3], matte_white));
  // Right
  primitives_.push_back (CreatePrimitive (triangles[4], matte_green));
  primitives_.push_back (CreatePrimitive (triangles[5], matte_green));
  // Left
  primitives_.push_back (CreatePrimitive (triangles[6], matte_red));
  primitives_.push_back (CreatePrimitive (triangles[7], matte_red));
  // Front
  primitives_.push_back (CreatePrimitive (triangles[8], matte_tex));
  primitives_.push_back (CreatePrimitive (triangles[9], matte_tex));
  // Light
  primitives_.push_back (CreatePrimitive (triangles[10], matte_light));
  primitives_.push_back (CreatePrimitive (triangles[11], matte_light));

  std::shared_ptr <Texture> roughness (new ValueTexture (Spectrum (0.5)));
  std::shared_ptr <Texture> ior (new ValueTexture (Spectrum (1.35)));
  std::shared_ptr <Metal> metal (new Metal (white,
                                            roughness,
                                            roughness,
                                            ior,
                                            nullptr));
  // Sphere
  const std::shared_ptr <Shape> sphere
    = CreateSphere (Point3f (40, 15, 40), 15);
  // primitives_.push_back (CreatePrimitive (sphere, metal));

}
/*
// ---------------------------------------------------------------------------
*/
auto Scene::BuildBokehScene () -> void
{
  RandomSampler sampler;

  std::array <std::shared_ptr <Texture>, 5> texs;
  texs[0] = CreateValueTexture (Spectrum (0.75, 0.2, 0.2));
  texs[1] = CreateValueTexture (Spectrum (0.2, 0.2, 0.75));
  texs[2] = CreateValueTexture (Spectrum (0.2, 0.75, 0.2));
  texs[3] = CreateValueTexture (Spectrum (0.75, 0.75, 0.75));
  texs[4] = CreateValueTexture (Spectrum::Zero ());

  std::array <std::shared_ptr <Shape>, 11> spheres;
  spheres[0] = CreateSphere (Point3f (0, -1e-8, 0), 1e8);
  for (int i = 1; i < 11; ++i)
  {
    const Float px = 40.0 * sampler.SampleFloat ();
    const Float py = 40.0 * sampler.SampleFloat ();
    const Float pz = 40.0 * sampler.SampleFloat ();
    const Float r  = 5.0  * sampler.SampleFloat ();
    spheres[i] = CreateSphere (Point3f (px, py, pz), r);
  }

  std::shared_ptr <Material> light (new Matte (texs[4], texs[3]));

  std::vector <std::shared_ptr <Primitive>> primitives (11);
  for (int i = 0; i < 11; ++i)
  {
    int idx = std::floor (4 * sampler.SampleFloat ());
    std::shared_ptr <Material> mat (new Matte (texs[idx], nullptr));

    if (i % 3 == 0)
    {
      primitives[i] = CreatePrimitive (spheres[i], light);
      continue;
    }
    primitives[i] = CreatePrimitive (spheres[i], mat);
  }

  std::swap (primitives, primitives_);
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
