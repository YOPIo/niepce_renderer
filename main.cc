#include "core/niepce.h"

#include "cameras/camera.h"

#include "randoms/xorshift.h"

#include "shapes/sphere.h"

#include "materials/material.h"

#include "geometries/point2.h"
#include "geometries/point3.h"
#include "geometries/point4.h"
#include "geometries/vector2.h"
#include "geometries/vector3.h"
#include "geometries/vector4.h"
#include "geometries/normal3.h"
#include "primitives/primitive.h"

#include "core/transform.h"
#include "core/ray.h"

#ifdef _OPENMP
#include <omp.h>
#endif // _OPENMP

namespace niepce
{

// ---------------------------------------------------------------------------
// Scene definition
// ---------------------------------------------------------------------------

Lambert* white = new Lambert(Vector3f(0, 0, 0), Vector3f(0.8, 0.8, 0.8));
Lambert* red   = new Lambert(Vector3f(0, 0, 0), Vector3f(0.8, 0.3, 0.3));
Lambert* green = new Lambert(Vector3f(0, 0, 0), Vector3f(0.3, 0.8, 0.3));


std::vector<Primitive> scene =
{
  // Left
  Primitive(new Sphere(Point3f(-1e5 - 5, 0, 0), 1e5), green),
  // Right
  Primitive(new Sphere(Point3f( 1e5 + 5, 0, 0), 1e5), red),
  // Ceiling
  Primitive(new Sphere(Point3f(0,  1e5 + 5, 0), 1e5), white),
  // Floor
  Primitive(new Sphere(Point3f(0, -1e5 - 5, 0), 1e5), white),
  // Back
  Primitive(new Sphere(Point3f(0, 0, -1e5 - 5), 1e5), white),
  // Front
  Primitive(new Sphere(Point3f(0, +1e5 + 5, 0), 1e5), white),
};

auto Render() -> void
{
  // ---------------------------------------------------------------------------
  // Camera settings
  // ---------------------------------------------------------------------------
  Transform camera = LookAt(Point3f(0, 0, 18),  // Position
                            Point3f(0, 0, 0),   // Lookat
                            Vector3f(0, 1, 0)); // Up

  // Create image buffer
  std::unique_ptr<Vector3f[]> image(new Vector3f[kWidth * kHeight]);
  for (int i = 0; i < kWidth * kHeight; ++i) { image[i] = Vector3f(0.0, 0.0, 0.0); }

  // Start rendering
  for (int y = 0; y < kHeight; ++y)
  {
    std::cerr << 100.0 * ((float)y / (float)kHeight) << "                   \r";
#pragma omp parallel for schedule(static) // OpenMP
    for (int x = 0; x < kWidth; ++x)
    {
      const unsigned int idx = (kHeight - y - 1) * kWidth + x;
      // Super sampling 2x2
      for (int sx = 0; sx < 2; ++sx)
      {
        for (int sy = 0; sy < 2; ++sy)
        {
          Vector3f buf;
          for (int i = 0; i < kSamples; ++i)
          {
            /*
            const Ray ray = camera.GenerateRay(x, y, sx, sy);
            buf = buf + Radiance(scene, ray, 0) /
                ((static_cast<Float>(kSamples) * (2.0 * 2.0)));
            */
          }
          image[idx] = image[idx] + buf;
        }
      }
    }
  }

  // Save as .ppm format
  auto ToLDR = [](Float v)
      {
        v = v < 0.0 ? 0.0 : (v > 1.0 ? 1.0 : v);
        return static_cast<int>(std::pow(v, 1.0 / 2.2) * 255 + 0.5);
      };
  // Write image to PPM file.
  FILE *f = fopen("image.ppm", "wb");
  fprintf(f, "P3\n%d %d\n%d\n", kWidth, kHeight, 255);
  for (int i = 0; i < kWidth * kHeight; ++i)
  {
    fprintf(f, "%d %d %d ", ToLDR(image[i].x), ToLDR(image[i].y), ToLDR(image[i].z));
  }
  fclose(f);
}

auto IsIntersect(const Ray&   ray,
                 Interaction* interaction,
                 Primitive*   primitive) -> bool
{
  interaction->t = -1.0;
  for (auto& s : scene)
  {
    Interaction inter;
    if (s.IsIntersect(ray, &inter))
    {
      if (inter.t < interaction->t)
      {
        *interaction = inter;
        primitive    = &s;
      }
    }
  }
  return interaction->t != -1.0;
}

auto Radiance(const std::vector<Sphere>& scene,
              const Ray&                 ray,
              const int                  depth) -> Vector3f
{
  if (depth > kMaxDepth)
  {
    return Vector3f(0, 0, 0);
  }

  // Intersection
  Interaction inter;
  Primitive   p;
  if ( !IsIntersect(ray, &inter, &p) )
  {
    // Is not hit.
    return Vector3f(0.0, 0.0, 0.0);
  }

  // Get material
  std::shared_ptr<Material> mtl = p.GetMaterial();

  // Handle case, hit with light
  if (mtl->GetMaterialType() == MaterialType::kLight)
  {
    // Return emission
    return Vector3f(1, 1, 1);
  }

  Float    pdf ;
  Vector3f brdf;
  // Sample next ray
  const Ray next_ray = mtl->SampleRay(inter.position, ray.direction, inter.normal, &pdf, &brdf);

  // Compute cos
  const Float cos_t = Dot(inter.normal, next_ray.direction);

  // Monte carlo
  return Mult(mtl->Emission() + brdf, Radiance(scene, next_ray, depth + 1) * cos_t / pdf);
}

}  // namespace niepce


// ---------------------------------------------------------------------------
// main
// ---------------------------------------------------------------------------
auto main(int argc, char *argv[]) -> int
{
  niepce::Render();
  return 0;
}
