#include "niepce.h"
#include "vector3.h"
#include "ray.h"
#include "camera.h"
#include "random.h"
#include "sphere.h"
#include "material.h"

#ifdef _OPENMP
#include <omp.h>
#endif // _OPENMP

auto IsIntersect(const std::vector<Sphere>& scene,
                 const Ray&                 ray,
                 Float*                     t,
                 std::shared_ptr<Material>* material) -> bool;

auto Radiance(const std::vector<Sphere>& scene,
              const Ray&                 ray,
              const int
              depth) -> Vector3f;


auto main(int argc, char *argv[]) -> int
{
  // ---------------------------------------------------------------------------
  // Build scene
  // ---------------------------------------------------------------------------
  std::shared_ptr<Material> white (new Diffuse( Vector3f(0.0, 0.0, 0.0), Vector3f(0.8, 0.8, 0.8) ));
  std::shared_ptr<Material> red   (new Diffuse( Vector3f(0.0, 0.0, 0.0), Vector3f(0.8, 0.1, 0.1) ));
  std::shared_ptr<Material> green (new Diffuse( Vector3f(0.0, 0.0, 0.0), Vector3f(0.1, 0.8, 0.1) ));
  std::shared_ptr<Material> glass (new Glass  ( Vector3f(0.0, 0.0, 0.0), Vector3f(0.8, 0.8, 0.8), 1.32 ));
  std::shared_ptr<Material> light (new Light  ( Vector3f(3.0, 3.0, 3.0), Vector3f(0.0, 0.0, 0.0) ));

  const std::vector<Sphere> scene =
  {
    Sphere( 1e5, Vector3f( -1e5 - 5,         0,          0), red),   // left
    Sphere( 1e5, Vector3f(        0,   1e5 + 5,          0), white), // top
    Sphere( 1e5, Vector3f(        0,  -1e5 - 5,          0), white), // down
    Sphere( 1e5, Vector3f(        0,         0,   1e5 + 20), white), // front
    Sphere( 1e5, Vector3f(  1e5 + 5,         0,          0), green), // right
    Sphere( 1e5, Vector3f(        0,         0,  -1e5 -  5), white), // back
    Sphere(   1, Vector3f(        0,        -4,          0), red),   // Diffuse
    Sphere(   1, Vector3f(      2.5,        -4,          0), glass), // Glass
    Sphere( 0.7, Vector3f(        0,         4,          0), light)  // light
  };


  // ---------------------------------------------------------------------------
  // Camera settings
  // ---------------------------------------------------------------------------
  Camera camera(Vector3f(0, 0, 18), // Position
                Vector3f(0, 0, 1),  // Lookat
                Vector3f(0, 1, 0)); // Up

  // Create image buffer
  std::unique_ptr<Vector3f[]> image(new Vector3f[kWidth * kHeight]);
  for (int i = 0; i < kWidth * kHeight; ++i) { image[i] = Vector3f(0.0, 0.0, 0.0); }

  // Start rendering
#pragma omp parallel for
  for (int y = 0; y < kHeight; ++y)
  {
    std::cerr << 100.0 * ((float)y / (float)kHeight) << "                   \r";
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
            const Ray ray = camera.GenerateRay(x, y, sx, sy);
            buf = buf + Radiance(scene, ray, 0) /
                (static_cast<Float>(kSamples) * (2.0 * 2.0));
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

  return 0;
}

auto IsIntersect(const std::vector<Sphere>& scene,
                 const Ray&                 ray,
                 Float*                     t,
                 Sphere*                    shpere) -> bool
{
  *t = kInfinity;

  for (auto& s : scene)
  {
    Float d = kInfinity;
    if (s.IsIntersect(ray, &d))
    {
      if (d < *t && d > kEpsilon)
      {
        *t      = d;
        *shpere = s;
      }
    }
  }

  return *t != kInfinity ? true : false;
}

auto Radiance(const std::vector<Sphere>& scene,
              const Ray&                 ray,
              const int                  depth) -> Vector3f
{
  if (depth > kMaxDepth)
  {
    return Vector3f(0, 0, 0);
  }

  Sphere sphere;
  Float  t;
  if ( !IsIntersect(scene, ray, &t, &sphere) )
  {
    // Is not hit.
    return Vector3f(0.0, 0.0, 0.0);
  }

  // Get material
  const std::shared_ptr<Material> mtl = sphere.GetMaterial();

  // Handle case, hit with light
  if (mtl->MaterialType() == Material::Type::kLight)
  {
    return mtl->Emission();
  }

  // Compute hit point
  const Vector3f hitpoint = ray.origin + t * ray.direction;

  // Compute surface normal.
  const Vector3f normal = Normalize(hitpoint - sphere.GetPosition());


  Float    pdf ;
  Vector3f brdf;
  // Sample next ray
  const Ray next_ray = mtl->SampleRay(hitpoint, ray.direction, normal, &pdf, &brdf);

  // Compute cos
  const Float cos_t = Dot(normal, next_ray.direction);

  // Monte carlo
  return mtl->Emission() + Multiply( brdf, Radiance(scene, next_ray, depth + 1) ) * cos_t / pdf ;
}
