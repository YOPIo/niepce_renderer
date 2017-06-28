#include "path_tracer.h"

namespace niepce
{

PathTracer::PathTracer ()
{}

PathTracer::~PathTracer ()
{}

auto PathTracer::Render () -> void
{
  // Get render settings from scene
  const Settings settings = scene_->GetSettings ();

  // Create image buffer
  std::unique_ptr<Point2f[]> image (new Point2f[settings.width * settings.height]);

  // Loop for each pixel
  for (int y = 0; y < settings.height; ++y)
  {
    for (int x = 0; x < settings.width; ++x)
    {
      // Super sampling
      for (int sy = 0; sy < settings.super_samples; ++sy)
      {
        for (int sx = 0; sx = settings.super_samples; ++sx)
        {
          Point2f buf;
          for (int s = 0; s < settings.samples; ++s)
          {
            const Ray ray = camera_->GenerateRay(x, y, sx, sy);



          }
          image[y * settings.width + x] += buf;
        }
      }
    }
  }


}

auto PathTracer::RecursiveRender (const XorShift& rnd, unsigned int depth) -> Vector3f
{
  // TODO: Use russian roulette
  if (depth < 15)
  {
    return Vector3f ();
  }


}

}  // namespace niepce
