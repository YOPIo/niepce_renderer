#define TINYOBJLOADER_IMPLEMENTATION
#include "../3rdparty/tiny_obj_loader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../3rdparty/stb_image.h"

#include "render_manager.h"

namespace niepce
{

RenderManager::RenderManager()
{}

RenderManager::~RenderManager()
{}

// start rendering
auto RenderManager::Render(const Size& size,
                           int num_subpixel,
                           int num_sample_per_subpixel) -> void
{
  const int width  = size.Width();
  const int height = size.Height();
  for (int y = 0; y < height; ++y)
  {
    std::cerr << " Rendering status = " << (100.0 * y / height) << "%      \r";
    for (int x = 0; x < width; ++x)
    {
      const int idx = (height - y - 1) * width + x;
      Random random(y * width + x + 1);
      for (int sy = 0; sy < num_subpixel; ++sy)
      {
        for (int sx = 0; sx < num_subpixel; ++sx)
        {
          Rgb accumulated_radiance(0, 0, 0);
          for (int s = 0; s < num_sample_per_subpixel; ++s)
          {
            Ray ray = camera_->GenerateRay(width, height,
                                           x, y,
                                           sx, sy,
                                           num_subpixel);
            accumulated_radiance = accumulated_radiance + Radiance(ray, 0, random)
                / static_cast<Float>(num_sample_per_subpixel) / static_cast<Float>(num_subpixel * num_subpixel);
          }
          film_[idx] = film_[idx] + accumulated_radiance;
        }
      }
    }
  }
}

// load .obj file
auto RenderManager::LoadScene(const char* filename) -> void
{
  // TODO:
}

auto RenderManager::Radiance(const Ray& ray,
                             int        depth,
                             Random&    random) -> Rgb
{
  constexpr Rgb kBackgroundColor = glm::vec3(0.0, 0.0, 0.0);
  if (depth >= 10)
  {
    return kBackgroundColor;
  }

  HitRecord hit_record;
  const Face* hit_face = scene_.Intersect(ray, &hit_record);
  if (hit_face == nullptr)
  {
    return kBackgroundColor;
  }
  const std::shared_ptr<Material> mtl = hit_face->Material();
  const Rgb emission    = mtl->Emission();
  /*
  const Rgb reflectance = mtl->Reflectance();
  return reflectance;
  */
  if(emission.x > 0.0 || emission.y > 0.0 || emission.z > 0.0)
  {
    return emission;
  }
  Float pdf = -1;
  Rgb brdf = glm::vec3(0.0, 0.0, 0.0);

  const glm::vec3 next_direction = mtl->Sample(random, ray.direction_, hit_record.normal_, &pdf, &brdf);
  const Ray next_ray(hit_record.position_, next_direction);

  const Float cost = glm::dot(hit_record.normal_, next_direction);

  const Rgb radiance = Radiance(next_ray, depth + 1, random);
  const Rgb l = brdf * radiance * cost / pdf;
  return l;
}

auto RenderManager::BuildCornellBoxScene() -> void
{
  // create cornell box scene
  /*
  std::shared_ptr<Sphere> left    = std::make_shared<Sphere>(glm::vec3(  100000.0 + 1.0,             40.8,               81.6), 100000.0);
  std::shared_ptr<Sphere> right   = std::make_shared<Sphere>(glm::vec3(-100000.0 + 99.0,             40.8,               81.6), 100000.0);
  std::shared_ptr<Sphere> back    = std::make_shared<Sphere>(glm::vec3(            50.0,             40.8,           100000.0), 100000.0);
  std::shared_ptr<Sphere> front   = std::make_shared<Sphere>(glm::vec3(            50.0,             40.8,  -100000.0 + 250.0), 100000.0);
  std::shared_ptr<Sphere> floor   = std::make_shared<Sphere>(glm::vec3(            50.0,         100000.0,               81.6), 100000.0);
  std::shared_ptr<Sphere> ceiling = std::make_shared<Sphere>(glm::vec3(            50.0, -100000.0 + 81.6,               81.6), 100000.0);
  std::shared_ptr<Sphere> light   = std::make_shared<Sphere>(glm::vec3(            50.0,             90.0,               81.6),     15.0);
  std::shared_ptr<Sphere> sphere1 = std::make_shared<Sphere>(glm::vec3(            65.0,             20.0,               20.0),     20.0);
  std::shared_ptr<Sphere> sphere2 = std::make_shared<Sphere>(glm::vec3(            27.0,             16.5,               47.0),     16.5);
  std::shared_ptr<Sphere> sphere3 = std::make_shared<Sphere>(glm::vec3(            77.0,             16.5,               78.0),     16.5);
  */

  std::shared_ptr<Sphere> left    = std::make_shared<Sphere>(glm::vec3(-1e5 - 12.5,         0.0,         0.0),  1e5);
  std::shared_ptr<Sphere> right   = std::make_shared<Sphere>(glm::vec3( 1e5 + 12.5,         0.0,         0.0),  1e5);
  std::shared_ptr<Sphere> back    = std::make_shared<Sphere>(glm::vec3(        0.0,         0.0, -1e5 - 12.5),  1e5);
  std::shared_ptr<Sphere> front   = std::make_shared<Sphere>(glm::vec3(        0.0,         0.0,  1e5 + 50.0),  1e5);
  std::shared_ptr<Sphere> floor   = std::make_shared<Sphere>(glm::vec3(        0.0, -1e5 - 12.5,         0.0),  1e5);
  std::shared_ptr<Sphere> ceiling = std::make_shared<Sphere>(glm::vec3(        0.0,  1e5 + 12.5,         0.0),  1e5);
  std::shared_ptr<Sphere> light   = std::make_shared<Sphere>(glm::vec3(        0.0,        10.0,         0.0),  3.0);
  std::shared_ptr<Sphere> sphere1 = std::make_shared<Sphere>(glm::vec3(        8.8,        -9.5,         6.5),  3.0);
  std::shared_ptr<Sphere> sphere2 = std::make_shared<Sphere>(glm::vec3(       -6.3,        -9.0,         6.0),  3.5);
  std::shared_ptr<Sphere> sphere3 = std::make_shared<Sphere>(glm::vec3(        0.8,        -9.0,         8.0),  3.5);

  // create materials
  std::shared_ptr<Material> red_matt   = std::make_shared<Lambert>("red",   Rgb(0,  0,  0), Rgb(0.75, 0.25, 0.25));
  std::shared_ptr<Material> green_matt = std::make_shared<Lambert>("green", Rgb(0,  0,  0), Rgb(0.25, 0.75, 0.25));
  std::shared_ptr<Material> white_matt = std::make_shared<Lambert>("white", Rgb(0,  0,  0), Rgb(0.75, 0.75, 0.75));
  std::shared_ptr<Phong>    phong_matt = std::make_shared<Phong>("phong",   Rgb(0, 0, 0),   Rgb(0.99, 0.99, 0.99), 100);
  std::shared_ptr<Light>    light_matt = std::make_shared<Light>("light",   Rgb(1,  1,  1), Rgb(   0,    0,    0));


  // define faces, setup scene
  scene_.Append( Face(right,   red_matt)   );
  scene_.Append( Face(left,    green_matt) );
  scene_.Append( Face(back,    white_matt) );
  scene_.Append( Face(front,   white_matt) );
  scene_.Append( Face(floor,   white_matt) );
  scene_.Append( Face(ceiling, white_matt) );
  scene_.Append( Face(sphere1, green_matt) );
  scene_.Append( Face(sphere2, red_matt)   );
  scene_.Append( Face(sphere3, green_matt) );
  scene_.Append( Face(light,   light_matt) );

  SetupCameraForCornellBox();
}

auto RenderManager::SetupCameraForCornellBox() -> void
{
  if (camera_)
  {
    camera_.reset();
  }
  /*
  const glm::vec3 position(50.0, 45.0, 220.0);
  const glm::vec3 lookat(glm::vec3(0.0, -0.04, -1.0) + position);
  const glm::vec3 up(0.0, 1.0, 0.0);
  */
  const glm::vec3 position(0.0, 0.0, 40);
  const glm::vec3 lookat(0.0, 0.0, 0.0);
  const glm::vec3 up(0.0, 1.0, 0.0);
  const Float     distance    = 35.0;
  const Float     sensor_size = 30.0;

  camera_ = std::make_unique<PinholeCamera>(position,
                                            lookat,
                                            up,
                                            distance,
                                            sensor_size);
}

auto RenderManager::InitializeFilm(const Size& size) -> void
{
  film_ = Film(size);
}

auto RenderManager::RenderCornellBox(const char* filename,
                                     const Size& size,
                                     int num_sample,
                                     int num_super_sample) -> void
{
  DEBUG("Setup CornellBox.");
  BuildCornellBoxScene();
  DEBUG("Build Sccessful.");
  DEBUG("Initialize Camera and Film.");
  SetupCameraForCornellBox();
  InitializeFilm(size);
  DEBUG("Initialize Complete.");
  DEBUG("Start Rendering.");
  Render(size, num_sample, num_super_sample);
  DEBUG("Save Image.");
  SaveAs(filename);
}

auto RenderManager::SaveAs(const char* filename) -> void
{
  film_.SaveAs(filename);
}

} // namespace niepce
