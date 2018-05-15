/*!
 * @file scene.cc
 * @brief 
 * @author Masashi Yoshida
 * @date 2018/5/5
 * @details 
 */
#include "scene.h"
#include "../material/matte.h"
#include "../shape/triangle.h"
#include "../texture/image_texture.h"
#include "../texture/value_texture.h"
#include "../accelerator/aggregation.h"
#include "../primitive/primitive.h"
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
  std::shared_ptr <Texture> light = CreateValueTexture (Vector3f (10));
  std::shared_ptr <Texture> tex = CreateImageTexture ("/home/yopio/workspace/niepce/asset/test.png");

  // Generate materials.
  std::shared_ptr <Material> matte_white (new Matte (white, black));
  std::shared_ptr <Material> matte_red   (new Matte (red,   black));
  std::shared_ptr <Material> matte_green (new Matte (green, black));
  std::shared_ptr <Material> matte_light (new Matte (black, light));
  std::shared_ptr <Material> matte_tex   (new Matte (tex,   black));

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

  // Sphere
  const std::shared_ptr <Shape> sphere = CreateSphere (Point3f (50, 15, 50), 15);
  primitives_.push_back (CreatePrimitive (sphere, matte_white));
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
