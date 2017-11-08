#include "scene_utils.h"
#include "../camera/camera.h"
#include "../shape/vertex.h"
#include "../shape/shape.h"
#include "../shape/triangle.h"
#include "../texture/texture.h"
#include "../texture/constant_texture.h"
#include "../texture/image_map.h"
#include "../material/material.h"
#include "../material/matte.h"
#include "../material/mirror.h"
#include "../material/microfacet_test.h"
#include "../material/glass.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
auto CreateCornellBox () -> std::pair<std::shared_ptr<Camera>, Scene>
{
  // Camera creation
  const Point3f  position (275.0, 275.0, 1500.0);
  const Point3f  lookat   (275.0, 275.0,    0.0);
  const Vector3f up       (  0.0,   1.0,    0.0);
  const std::shared_ptr<Camera> camera (new Camera (position,
                                                    lookat,
                                                    up,
                                                    30,
                                                    (Float)kWidth / (Float)kHeight));

  // Cornell box
  // Positions generation
  std::array<std::shared_ptr<Point3f>, 28> positions;
  // Main body
  positions[ 0].reset (new Point3f (  0.0,   0.0,   0.0));
  positions[ 1].reset (new Point3f (550.0,   0.0,   0.0));
  positions[ 2].reset (new Point3f (550.0,   550,   0.0));
  positions[ 3].reset (new Point3f (  0.0,   550,   0.0));
  positions[ 4].reset (new Point3f (  0.0,   0.0, 550.0));
  positions[ 5].reset (new Point3f (550.0,   0.0, 550.0));
  positions[ 6].reset (new Point3f (550.0, 550.0, 550.0));
  positions[ 7].reset (new Point3f (  0.0, 550.0, 550.0));
  // Light
  positions[ 8].reset (new Point3f (200.0, 549.5, 200.0));
  positions[ 9].reset (new Point3f (380.0, 549.5, 200.0));
  positions[10].reset (new Point3f (380.0, 549.5, 380.0));
  positions[11].reset (new Point3f (200.0, 549.5, 380.0));
  // Short block (right)
  positions[12].reset (new Point3f (265.0,   0.0, 406.0));
  positions[13].reset (new Point3f (423.0,   0.0, 423.0));
  positions[14].reset (new Point3f (472.0,   0.0, 296.0));
  positions[15].reset (new Point3f (314.0,   0.0, 247.0));
  positions[16].reset (new Point3f (265.0, 165.0, 406.0));
  positions[17].reset (new Point3f (423.0, 165.0, 423.0));
  positions[18].reset (new Point3f (472.0, 165.0, 296.0));
  positions[19].reset (new Point3f (314.0, 165.0, 247.0));
  // Tall block (left)
  positions[20].reset (new Point3f ( 82.0,   0.0, 114.0));
  positions[21].reset (new Point3f (130.0,   0.0, 272.0));
  positions[22].reset (new Point3f (290.0,   0.0, 225.0));
  positions[23].reset (new Point3f (240.0,   0.0,  65.0));
  positions[24].reset (new Point3f ( 82.0, 330.0, 114.0));
  positions[25].reset (new Point3f (130.0, 330.0, 272.0));
  positions[26].reset (new Point3f (290.0, 330.0, 225.0));
  positions[27].reset (new Point3f (240.0, 330.0,  65.0));

  // Vertex generation
  std::array<std::shared_ptr<Vertex>, 28> vertices;
  // Main body
  vertices[ 0].reset (new Vertex (positions[ 0], nullptr, nullptr));
  vertices[ 1].reset (new Vertex (positions[ 1], nullptr, nullptr));
  vertices[ 2].reset (new Vertex (positions[ 2], nullptr, nullptr));
  vertices[ 3].reset (new Vertex (positions[ 3], nullptr, nullptr));
  vertices[ 4].reset (new Vertex (positions[ 4], nullptr, nullptr));
  vertices[ 5].reset (new Vertex (positions[ 5], nullptr, nullptr));
  vertices[ 6].reset (new Vertex (positions[ 6], nullptr, nullptr));
  vertices[ 7].reset (new Vertex (positions[ 7], nullptr, nullptr));
  // Light
  vertices[ 8].reset (new Vertex (positions[ 8], nullptr, nullptr));
  vertices[ 9].reset (new Vertex (positions[ 9], nullptr, nullptr));
  vertices[10].reset (new Vertex (positions[10], nullptr, nullptr));
  vertices[11].reset (new Vertex (positions[11], nullptr, nullptr));
  // Short block
  vertices[12].reset (new Vertex (positions[12], nullptr, nullptr));
  vertices[13].reset (new Vertex (positions[13], nullptr, nullptr));
  vertices[14].reset (new Vertex (positions[14], nullptr, nullptr));
  vertices[15].reset (new Vertex (positions[15], nullptr, nullptr));
  vertices[16].reset (new Vertex (positions[16], nullptr, nullptr));
  vertices[17].reset (new Vertex (positions[17], nullptr, nullptr));
  vertices[18].reset (new Vertex (positions[18], nullptr, nullptr));
  vertices[19].reset (new Vertex (positions[19], nullptr, nullptr));
  // Tall block
  vertices[20].reset (new Vertex (positions[20], nullptr, nullptr));
  vertices[21].reset (new Vertex (positions[21], nullptr, nullptr));
  vertices[22].reset (new Vertex (positions[22], nullptr, nullptr));
  vertices[23].reset (new Vertex (positions[23], nullptr, nullptr));
  vertices[24].reset (new Vertex (positions[24], nullptr, nullptr));
  vertices[25].reset (new Vertex (positions[25], nullptr, nullptr));
  vertices[26].reset (new Vertex (positions[26], nullptr, nullptr));
  vertices[27].reset (new Vertex (positions[27], nullptr, nullptr));

  // Create shapes from vertices
  std::array<std::shared_ptr<Shape>, 32> shapes;
  // Floor
  shapes[ 0].reset (new Triangle (vertices[ 0], vertices[ 4], vertices[ 1]));
  shapes[ 1].reset (new Triangle (vertices[ 1], vertices[ 4], vertices[ 5]));
  // Celling
  shapes[ 2].reset (new Triangle (vertices[ 2], vertices[ 6], vertices[ 7]));
  shapes[ 3].reset (new Triangle (vertices[ 2], vertices[ 7], vertices[ 3]));
  // Front wall
  shapes[ 4].reset (new Triangle (vertices[ 0], vertices[ 1], vertices[ 3]));
  shapes[ 5].reset (new Triangle (vertices[ 1], vertices[ 2], vertices[ 3]));
  // Red right wall
  shapes[ 6].reset (new Triangle (vertices[ 2], vertices[ 5], vertices[ 6]));
  shapes[ 7].reset (new Triangle (vertices[ 1], vertices[ 5], vertices[ 2]));
  // Green left wall
  shapes[ 8].reset (new Triangle (vertices[ 0], vertices[ 3], vertices[ 4]));
  shapes[ 9].reset (new Triangle (vertices[ 3], vertices[ 7], vertices[ 4]));
  // Light
  shapes[10].reset (new Triangle (vertices[ 8], vertices[ 9], vertices[10]));
  shapes[11].reset (new Triangle (vertices[ 8], vertices[10], vertices[11]));
  // Short block (right)
  shapes[12].reset (new Triangle (vertices[12], vertices[13], vertices[17])); // left side
  shapes[13].reset (new Triangle (vertices[12], vertices[17], vertices[16]));
  shapes[14].reset (new Triangle (vertices[13], vertices[14], vertices[17])); // front
  shapes[15].reset (new Triangle (vertices[14], vertices[18], vertices[17]));
  shapes[16].reset (new Triangle (vertices[15], vertices[18], vertices[14])); // right side
  shapes[17].reset (new Triangle (vertices[15], vertices[19], vertices[18]));
  shapes[18].reset (new Triangle (vertices[15], vertices[16], vertices[19])); // back
  shapes[19].reset (new Triangle (vertices[12], vertices[16], vertices[15]));
  shapes[20].reset (new Triangle (vertices[17], vertices[18], vertices[19])); // top
  shapes[21].reset (new Triangle (vertices[16], vertices[17], vertices[19]));
  // Tall block (left)
  shapes[22].reset (new Triangle (vertices[20], vertices[21], vertices[24])); // left side
  shapes[23].reset (new Triangle (vertices[21], vertices[25], vertices[24]));
  shapes[24].reset (new Triangle (vertices[21], vertices[22], vertices[25])); // front
  shapes[25].reset (new Triangle (vertices[22], vertices[26], vertices[25]));
  shapes[26].reset (new Triangle (vertices[22], vertices[23], vertices[27])); // right side
  shapes[27].reset (new Triangle (vertices[22], vertices[27], vertices[26]));
  shapes[28].reset (new Triangle (vertices[20], vertices[24], vertices[23])); // back
  shapes[29].reset (new Triangle (vertices[23], vertices[24], vertices[27]));
  shapes[30].reset (new Triangle (vertices[24], vertices[25], vertices[26])); // top
  shapes[31].reset (new Triangle (vertices[24], vertices[26], vertices[27]));

  // Create texture
  const std::shared_ptr<Texture<Spectrum>> white_map
      (new ConstantTexture<Spectrum> (0.75));

  const std::shared_ptr<Texture<Spectrum>> red_map
      (new ConstantTexture<Spectrum> (Spectrum (0.5, 0.25, 0.25, 0.0)));

  const std::shared_ptr<Texture<Spectrum>> green_map
      (new ConstantTexture<Spectrum> (Spectrum (0.25, 0.5, 0.25, 0.0)));

  // Create materials
  std::shared_ptr<Material> white_matte (new Matte (white_map));
  std::shared_ptr<Material> red_matte   (new Matte (red_map));
  std::shared_ptr<Material> green_matte (new Matte (green_map));

  std::shared_ptr<Texture<Spectrum>> white
      (new ConstantTexture<Spectrum> (Spectrum (0.75)));
  std::shared_ptr<Texture<Float>> ior
      (new ConstantTexture<Float> (1.21));
  std::shared_ptr<Texture<Float>> rough
      (new ConstantTexture<Float> (0.1));

  std::shared_ptr<Material> microfacet
      (std::make_shared<Microfacet> (white, white, rough, rough, ior));

  // Create lights
  std::shared_ptr<Light> light (new AreaLight (Spectrum (15.0)));

  // Create primitives
  std::vector<std::shared_ptr<Individual>> primitives (32);
  primitives[ 0].reset (new Individual (shapes[ 0], white_matte, nullptr));
  primitives[ 1].reset (new Individual (shapes[ 1], white_matte, nullptr));
  primitives[ 2].reset (new Individual (shapes[ 2], white_matte, nullptr));
  primitives[ 3].reset (new Individual (shapes[ 3], white_matte, nullptr));
  primitives[ 4].reset (new Individual (shapes[ 4], white_matte, nullptr));
  primitives[ 5].reset (new Individual (shapes[ 5], white_matte, nullptr));
  primitives[ 6].reset (new Individual (shapes[ 6], green_matte, nullptr));
  primitives[ 7].reset (new Individual (shapes[ 7], green_matte, nullptr));
  primitives[ 8].reset (new Individual (shapes[ 8],   red_matte, nullptr));
  primitives[ 9].reset (new Individual (shapes[ 9],   red_matte, nullptr));
  primitives[10].reset (new Individual (shapes[10],     nullptr,   light));
  primitives[11].reset (new Individual (shapes[11],     nullptr,   light));
  primitives[12].reset (new Individual (shapes[12], white_matte, nullptr));
  primitives[13].reset (new Individual (shapes[13], white_matte, nullptr));
  primitives[14].reset (new Individual (shapes[14], white_matte, nullptr));
  primitives[15].reset (new Individual (shapes[15], white_matte, nullptr));
  primitives[16].reset (new Individual (shapes[16], white_matte, nullptr));
  primitives[17].reset (new Individual (shapes[17], white_matte, nullptr));
  primitives[18].reset (new Individual (shapes[18], white_matte, nullptr));
  primitives[19].reset (new Individual (shapes[19], white_matte, nullptr));
  primitives[20].reset (new Individual (shapes[20], white_matte, nullptr));
  primitives[21].reset (new Individual (shapes[21], white_matte, nullptr));
  primitives[22].reset (new Individual (shapes[22], white_matte, nullptr));
  primitives[23].reset (new Individual (shapes[23], white_matte, nullptr));
  primitives[24].reset (new Individual (shapes[24], white_matte, nullptr));
  primitives[25].reset (new Individual (shapes[25], white_matte, nullptr));
  primitives[26].reset (new Individual (shapes[26], white_matte, nullptr));
  primitives[27].reset (new Individual (shapes[27], white_matte, nullptr));
  primitives[28].reset (new Individual (shapes[28], white_matte, nullptr));
  primitives[29].reset (new Individual (shapes[29], white_matte, nullptr));
  primitives[30].reset (new Individual (shapes[30], white_matte, nullptr));
  primitives[31].reset (new Individual (shapes[31], white_matte, nullptr));

  Scene scene (primitives, AcceleratorType::kNone);
  scene.LoadIbl ("../../assets/test.hdr");

  return std::make_pair (camera, scene);
}
/*
// ---------------------------------------------------------------------------
*/
auto SphereAndPlane () -> std::pair<std::shared_ptr<Camera>, Scene>
{
  // Camera creation
  const Point3f  position (8.0, 25.0, 20.0);
  const Point3f  lookat   (0.0,  2.0,  0.0);
  const Vector3f up       (0.0,  0.0,  1.0);
  const std::shared_ptr<Camera> camera (new Camera (position,
                                                    lookat,
                                                    up,
                                                    30,
                                                    (Float)kWidth / (Float)kHeight));

  std::array<std::shared_ptr<Point3f>, 8> positions;
  positions[0].reset (new Point3f (-30.0,    0, -30.0));
  positions[1].reset (new Point3f ( 30.0,    0, -30.0));
  positions[2].reset (new Point3f (-30.0,    0,  30.0));
  positions[3].reset (new Point3f ( 30.0,    0,  30.0));
  positions[4].reset (new Point3f (-15.0, 30.0, -15.0));
  positions[5].reset (new Point3f ( 15.0, 30.0, -15.0));
  positions[6].reset (new Point3f (-15.0, 30.0,  15.0));
  positions[7].reset (new Point3f ( 15.0, 30.0,  15.0));

  std::array<std::shared_ptr<Vertex>, 8> vertices;
  vertices[0].reset (new Vertex (positions[0], nullptr, nullptr));
  vertices[1].reset (new Vertex (positions[1], nullptr, nullptr));
  vertices[2].reset (new Vertex (positions[2], nullptr, nullptr));
  vertices[3].reset (new Vertex (positions[3], nullptr, nullptr));
  vertices[4].reset (new Vertex (positions[4], nullptr, nullptr));
  vertices[5].reset (new Vertex (positions[5], nullptr, nullptr));
  vertices[6].reset (new Vertex (positions[6], nullptr, nullptr));
  vertices[7].reset (new Vertex (positions[7], nullptr, nullptr));

  std::array<std::shared_ptr<Shape>, 7> shapes;
  shapes[0].reset (new Triangle (vertices[0], vertices[2], vertices[1]));
  shapes[1].reset (new Triangle (vertices[1], vertices[2], vertices[3]));
  shapes[2].reset (new Triangle (vertices[4], vertices[5], vertices[6]));
  shapes[3].reset (new Triangle (vertices[6], vertices[5], vertices[7]));
  shapes[4].reset (new Sphere (Point3f ( 0.0, 2.0, 0.0), 2.0));
  shapes[5].reset (new Sphere (Point3f ( 6.0, 2.0, 0.0), 2.0));
  shapes[6].reset (new Sphere (Point3f (-6.0, 2.0, 0.0), 2.0));

  std::shared_ptr<Texture<Spectrum>> white_map (new ConstantTexture<Spectrum> (0.75));

  std::shared_ptr<Material> matte  (new Matte  (white_map));
  std::shared_ptr<Mirror>   mirror (new Mirror (white_map));

  std::shared_ptr<Light> light (new AreaLight (1.0));

  std::vector<std::shared_ptr<Individual>> primitives (7);
  primitives[0].reset (new Individual (shapes[0], matte,   nullptr));
  primitives[1].reset (new Individual (shapes[1], matte,   nullptr));
  primitives[2].reset (new Individual (shapes[2], nullptr, light));
  primitives[3].reset (new Individual (shapes[3], nullptr, light));
  primitives[4].reset (new Individual (shapes[4], mirror,  nullptr));
  primitives[5].reset (new Individual (shapes[5], matte,   nullptr));
  primitives[6].reset (new Individual (shapes[6], matte,   nullptr));

  Scene scene (primitives, AcceleratorType::kNone);
  // scene.LoadIbl ("../../assets/test.hdr");

  return std::make_pair (camera, scene);
}
/*
// ---------------------------------------------------------------------------
*/
auto CreateComparisonSphereScene ()
-> std::pair<std::shared_ptr<Camera>, Scene>
{
  const Point3f  pos    (0.0, 30.0, 30.0);
  const Point3f  lookat (0.0,  3.0,  0.0);
  const Vector3f up     (0.0,  1.0,  0.0);
  const std::shared_ptr<Camera> camera (new Camera (pos,
                                                    lookat,
                                                    up,
                                                    45,
                                                    (Float)kWidth / (Float)kHeight));

  std::array<std::shared_ptr<Point3f>, 4> positions;
  positions[0].reset (new Point3f (-30.0, 0, -30.0));
  positions[1].reset (new Point3f ( 30.0, 0, -30.0));
  positions[2].reset (new Point3f (-30.0, 0,  30.0));
  positions[3].reset (new Point3f ( 30.0, 0,  30.0));

  std::array<std::shared_ptr<Vertex>, 4> vertices;
  vertices[0].reset (new Vertex (positions[0], nullptr, nullptr));
  vertices[1].reset (new Vertex (positions[1], nullptr, nullptr));
  vertices[2].reset (new Vertex (positions[2], nullptr, nullptr));
  vertices[3].reset (new Vertex (positions[3], nullptr, nullptr));

  std::vector<std::shared_ptr<Shape>> shapes;
  shapes.push_back
      (std::make_shared<Triangle>(vertices[0], vertices[2], vertices[1]));
  shapes.push_back
      (std::make_shared<Triangle>(vertices[1], vertices[2], vertices[3]));
  shapes.push_back
    (std::make_shared<Sphere> (Point3f (  0.0, 3.0, 0.0), 3.0));
  shapes.push_back
    (std::make_shared<Sphere> (Point3f (-10.0, 3.0, 0.0), 3.0));
  shapes.push_back
    (std::make_shared<Sphere> (Point3f ( 10.0, 3.0, 0.0), 3.0));

  std::shared_ptr<Texture<Spectrum>> white
      (new ConstantTexture<Spectrum> (Spectrum (0.75)));
  std::shared_ptr<Texture<Float>> ior
      (new ConstantTexture<Float> (1.21));
  std::shared_ptr<Texture<Float>> rough
      (new ConstantTexture<Float> (0.1));

  std::vector<std::shared_ptr<Material>> materials;
  materials.push_back (std::make_shared<Matte> (white));
  materials.push_back
      (std::make_shared<Microfacet> (white, white, rough, rough, ior));

  std::vector<std::shared_ptr<Individual>> primitives;
  primitives.push_back
      (std::make_shared<Individual> (shapes[0], materials[0], nullptr));
  primitives.push_back
      (std::make_shared<Individual> (shapes[1], materials[0], nullptr));
  primitives.push_back
      (std::make_shared<Individual> (shapes[2], materials[1], nullptr));
  primitives.push_back
      (std::make_shared<Individual> (shapes[3], materials[0], nullptr));
  primitives.push_back
      (std::make_shared<Individual> (shapes[4], materials[0], nullptr));

  Scene scene (primitives, AcceleratorType::kNone);
  scene.LoadIbl ("../../assets/test.hdr");

  return std::make_pair (camera, scene);
}
/*
// ---------------------------------------------------------------------------
*/
auto CreateSphereScene () -> std::pair<std::shared_ptr<Camera>, Scene>
{
  const Point3f  position (0, 50, 30);
  const Point3f  lookat   (0,  0,  2);
  const Vector3f up       (0,  0,  1);
  std::shared_ptr<Camera> camera (new Camera (position,
                                              lookat,
                                              up,
                                              50,
                                              (Float)(kWidth) / (Float)(kHeight)));

  std::vector<std::shared_ptr<Shape>> shapes;
  shapes.push_back (std::make_shared<Sphere> (Translate (Vector3f (-20, 0,    7.5)), 7.5));
  shapes.push_back (std::make_shared<Sphere> (Translate (Vector3f (  0, 0,    7.5)), 7.5));
  shapes.push_back (std::make_shared<Sphere> (Translate (Vector3f ( 20, 0,    7.5)), 7.5));
  shapes.push_back (std::make_shared<Sphere> (Translate (Vector3f (  0, 0, -10e10)), 10e10));
  shapes.push_back (std::make_shared<Sphere> (Translate (Vector3f (  0, 0,   1000)), 500));

  std::shared_ptr<Texture<Spectrum>> white
      (new ConstantTexture<Spectrum> (Spectrum (0.825)));
  std::shared_ptr<Texture<Float>> ior
      (new ConstantTexture<Float> (1.10));
  std::shared_ptr<Texture<Float>> rough
      (new ConstantTexture<Float> (0.3));
  std::shared_ptr<Texture<Spectrum>> transmittance
      (new ConstantTexture<Spectrum> (Spectrum (0.9)));

  std::vector<std::shared_ptr<Material>> materials;
  materials.push_back (std::make_shared<Matte> (white));
  materials.push_back
    (std::make_shared<Microfacet> (white, white, rough, rough, ior));
  materials.push_back
    (std::make_shared<Mirror> (white));
  materials.push_back
      (std::make_shared<Glass> (white, transmittance, ior));

  std::shared_ptr<Light> light (new AreaLight (Spectrum (3.0)));

  std::vector<std::shared_ptr<Individual>> primitives;
  primitives.push_back (std::make_shared<Individual> (shapes[0], materials[0], nullptr));
  primitives.push_back (std::make_shared<Individual> (shapes[1], materials[1], nullptr));
  primitives.push_back (std::make_shared<Individual> (shapes[2], materials[2], nullptr));
  primitives.push_back (std::make_shared<Individual> (shapes[3], materials[0], nullptr));
  primitives.push_back (std::make_shared<Individual> (shapes[4],      nullptr,   light));

  Scene scene (primitives, AcceleratorType::kNone);
  scene.LoadIbl ("../../assets/test.hdr");

  return std::make_pair (camera, scene);
}
/*
// ---------------------------------------------------------------------------
*/
auto CreateSphereCornellBox () -> std::pair<std::shared_ptr<Camera>, Scene>
{
  const Point3f  position (0.0, 49.9, 0.0);
  const Point3f  lookat   (0.0,  0.0, 0.0);
  const Vector3f up       (0.0,  0.0, 1.0);
  std::shared_ptr<Camera> camera (new Camera (position,
                                              lookat,
                                              up,
                                              75,
                                              (Float)(kWidth) / (Float)(kHeight)));

  std::vector<std::shared_ptr<Shape>> shapes;
  shapes.push_back (std::make_shared<Sphere> (Translate (Vector3f (        0.0,       -28.0,  650.0 - 0.20)), 600));  // Light
  shapes.push_back (std::make_shared<Sphere> (Translate (Vector3f (-1e5 - 50.0,         0.0,           0.0)), 1e5));  // Left
  shapes.push_back (std::make_shared<Sphere> (Translate (Vector3f ( 1e5 + 50.0,         0.0,           0.0)), 1e5));  // Right
  shapes.push_back (std::make_shared<Sphere> (Translate (Vector3f (        0.0,  1e5 + 50.0,           0.0)), 1e5));  // Back
  shapes.push_back (std::make_shared<Sphere> (Translate (Vector3f (        0.0, -1e5 - 50.0,           0.0)), 1e5));  // Front
  shapes.push_back (std::make_shared<Sphere> (Translate (Vector3f (        0.0,         0.0,   -1e5 - 50.0)), 1e5));  // Bottom
  shapes.push_back (std::make_shared<Sphere> (Translate (Vector3f (        0.0,         0.0,    1e5 + 50.0)), 1e5));  // Top
  shapes.push_back (std::make_shared<Sphere> (Translate (Vector3f (      -23.5,       -28.0,  -50.0 + 15.0)), 15.0)); // Sphere left
  shapes.push_back (std::make_shared<Sphere> (Translate (Vector3f (       23.5,       -28.0,  -50.0 + 15.0)), 15.0)); // Sphere right

  std::shared_ptr<Texture<Spectrum>> white
    (new ConstantTexture<Spectrum> (Spectrum (0.85)));
  std::shared_ptr<Texture<Spectrum>> red
    (new ConstantTexture<Spectrum> (Spectrum (0.75, 0.35, 0.35, 0.0)));
  std::shared_ptr<Texture<Spectrum>> green
    (new ConstantTexture<Spectrum> (Spectrum (0.35, 0.75, 0.35, 0.0)));
  std::shared_ptr<Texture<Float>> rough
      (new ConstantTexture<Float> (0.3));
  std::shared_ptr<Texture<Float>> ior
      (new ConstantTexture<Float> (1.10));
  std::shared_ptr<Texture<Spectrum>> transmittance
    (new ConstantTexture<Spectrum> (Spectrum::One ()));

  std::vector<std::shared_ptr<Material>> materials;
  materials.push_back (std::make_shared<Matte> (white));
  materials.push_back (std::make_shared<Matte> (red));
  materials.push_back (std::make_shared<Matte> (green));
  materials.push_back (std::make_shared<Mirror> (white));
  materials.push_back (std::make_shared<Microfacet> (white, transmittance, rough, rough, ior));

  std::shared_ptr<Light> light (new AreaLight (Spectrum (3.0)));

  std::vector<std::shared_ptr<Individual>> primitives;
  primitives.push_back (std::make_shared<Individual> (shapes[0],      nullptr,   light));
  primitives.push_back (std::make_shared<Individual> (shapes[1], materials[1], nullptr));
  primitives.push_back (std::make_shared<Individual> (shapes[2], materials[2], nullptr));
  primitives.push_back (std::make_shared<Individual> (shapes[3], materials[0], nullptr));
  primitives.push_back (std::make_shared<Individual> (shapes[4], materials[0], nullptr));
  primitives.push_back (std::make_shared<Individual> (shapes[5], materials[0], nullptr));
  primitives.push_back (std::make_shared<Individual> (shapes[6], materials[0], nullptr));
  primitives.push_back (std::make_shared<Individual> (shapes[7], materials[3], nullptr));
  primitives.push_back (std::make_shared<Individual> (shapes[8], materials[4], nullptr));

  Scene scene (primitives, AcceleratorType::kSah);
  return std::make_pair(camera, scene);
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
