/*!
 * @file path_tracer.cc
 * @brief 
 * @author Masashi Yoshida
 * @date 2018/4/23
 * @details 
 */
#include "path_tracer.h"
#include "../core/bounds2f.h"
#include "../core/ray.h"
#include "../core/intersection.h"
#include "../core/point3f.h"
#include "../core/vector3f.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
PathTracer::PathTracer
(
 const Scene& scene,
 const RenderSettings& settings
) :
  scene_    (scene),
  settings_ (settings),
  pool_     (settings.GetItem (RenderSettings::Item::kNumThread))
{}
/*
// ---------------------------------------------------------------------------
*/
auto PathTracer::Render () -> void
{
  // Generate the tiles
  const unsigned int tile_width
    = settings_.GetItem (RenderSettings::Item::kTileWidth);
  const unsigned int tile_height
    = settings_.GetItem (RenderSettings::Item::kTileHeight);

  const unsigned int resolution_width
    = settings_.GetItem (RenderSettings::Item::kWidth);
  const unsigned int resolution_height
    = settings_.GetItem (RenderSettings::Item::kHeight);
  const unsigned int num_sample
    = settings_.GetItem (RenderSettings::Item::kNumSamples);

  // Todo: Delete
  image_.reset (new Vector3f [resolution_width * resolution_height]);

  // Divide tile
  std::vector <Bounds2f> tile_bounds;
  for (unsigned int y = 0; y < resolution_height; y += tile_height)
  {
    for (unsigned int x = 0; x < resolution_width; x += tile_width)
    {
      const Point2f  min  (x, y);
      const Point2f  max  (x + tile_width - 1, y + tile_height - 1);
      const Bounds2f tile (min, max);
      tile_bounds.push_back (tile);
    }
  }

  std::unique_ptr <RandomSampler> sampler (new RandomSampler ());

  // Generate sampler for each tile.
  std::vector <std::unique_ptr <RandomSampler>> samplers;
  for (const auto& tile : tile_bounds)
  {
    const auto x = tile.Max ().X ();
    const auto y = tile.Min ().Y ();
    samplers.push_back (sampler->Clone (y * tile_width + x));
  }

  // The number of tiles and samplers should be same.
  if (samplers.size () != tile_bounds.size ())
  {
    return ;
  }

  // Register the tasks
  std::vector <std::future <void>> futures;
  for (unsigned int i = 0; i < tile_bounds.size (); ++i)
  {
    std::function <void (const Bounds2f&, RandomSampler*)> func
      = std::bind (&PathTracer::TraceRay,
                   this,
                   std::placeholders::_1,
                   std::placeholders::_2);
    futures.emplace_back (pool_.Enqueue (func,
                                         tile_bounds[i],
                                         samplers[i].get ()));
    /*
    // This is bug codes.
    auto task = [&] () { this->TraceRay (tile_bounds[i], samplers[i].get ()); };
    futures.emplace_back (pool_.Enqueue (task));
    */
  }

  // Wait for all task done.
  for (auto& future : futures)
  {
    future.wait ();
  }

  auto to_int = [] (Float x) -> int
  {
    int res = static_cast <unsigned char> (x * 255 - 1.0 + 0.5);
    if (res > 255) { std::cerr << res << "\n"; return 255; }
    if (res < 0)   { std::cerr << res << "\n"; return 0; }
    return res;
  };

  std::ofstream os ("pt.ppm");
  os << "P3\n" << resolution_width << " " << resolution_height << " 255\n";
  for (int i = 0; i < resolution_width * resolution_height; ++i)
  {
    const int red   = Clamp (to_int (image_[i].X ()), 0, 255);
    const int green = Clamp (to_int (image_[i].Y ()), 0, 255);
    const int blue  = Clamp (to_int (image_[i].Z ()), 0, 255);
    os << red << " " << green << " " << blue << " ";
  }
  os.close ();
}
/*
// ---------------------------------------------------------------------------
*/
auto PathTracer::TraceRay
(
 const Bounds2f& tile,
 RandomSampler* tile_sampler
)
  noexcept -> void
{
  const Point2f min = tile.Min ();
  const Point2f max = tile.Max ();

  const unsigned int tile_width
    = settings_.GetItem (RenderSettings::Item::kTileWidth);
  const unsigned int tile_height
    = settings_.GetItem (RenderSettings::Item::kTileHeight);

  const unsigned int resolution_width
    = settings_.GetItem (RenderSettings::Item::kWidth);
  const unsigned int resolution_height
    = settings_.GetItem (RenderSettings::Item::kHeight);
  const unsigned int num_sample
    = settings_.GetItem (RenderSettings::Item::kNumSamples);

  // Camera
  Ray cam (Point3f(50,50,350), Normalize (Vector3f(0, 0, -1)));
  Vector3f cx = Vector3f (resolution_width*.5135/resolution_height, 0, 0);
  Vector3f cy = Cross (cx, cam.Direction ()).Normalize () * .5135;

  for (unsigned int y = min.Y (); y <= max.Y (); ++y)
  {
    for (unsigned int x = min.X (); x <= max.X (); ++x)
    {
      const unsigned int idx = (resolution_height - y - 1) * resolution_width + x;
      for (unsigned sy = 0; sy < 2; ++sy)
      {
        for (unsigned int sx = 0; sx < 2; ++sx)
        {
          Vector3f r (0);
          for (unsigned int s = 0; s < num_sample; ++s)
          {
            // Generate ray.
            const Float r1 = 2.0 * tile_sampler->SampleFloat ();
            const Float r2 = 2.0 * tile_sampler->SampleFloat ();
            const Float dx = r1 < 1 ? std::sqrt (r1) - 1 : 1 - std::sqrt (2 - r1);
            const Float dy = r2 < 1 ? std::sqrt (r2) - 1 : 1 - std::sqrt (2 - r2);
            const Vector3f d = cx * (((sx +.5 + dx) / 2 + x) / resolution_width  - 0.5)
                             + cy * (((sy +.5 + dy) / 2 + y) / resolution_height - 0.5)
                             + cam.Direction ();
            const Ray ray (cam.Origin () + d * 140, d.Normalized ());

            r = r + Radiance (ray, tile_sampler)
              / ((static_cast <Float> (num_sample) * static_cast <Float> (4)));
          }
          image_[idx] = image_[idx] + r;
        }
      }
    }
  }
}
/*
// ---------------------------------------------------------------------------
*/
auto PathTracer::Radiance
(
 const Ray& first_ray,
 RandomSampler* tile_sampler
)
  -> Vector3f
{
  Vector3f l = Vector3f::Zero ();
  Vector3f f = Vector3f::One ();
  Ray ray (first_ray);

  // Render the tile.
  for (unsigned int depth = 0; ; ++depth)
  {
    // Intersect test.
    Intersection intersection;
    if (!scene_.IsIntersect (ray, &intersection))
    {
      return l;
      break;
    }

    // Ready to sample.
    const std::shared_ptr <Material> material = intersection.Material ();

    // Add contribution
    l = l + Multiply (f, material->Emission (intersection.Texcoord ()));

    // Russian roulette
    Float q = std::max ({l[0], l[1], l[2]});
    if (depth > 5)
    {
      if (tile_sampler->SampleFloat () >= q) { return l; }
    }
    else { q = 1.0; }

    // Sample incident direction.
    BsdfRecord bsdf_record (intersection);
    material->Sample (intersection, tile_sampler->SamplePoint2f (), &bsdf_record);

    // Calculate the weight.
    const Float cos_t = std::abs (Dot (bsdf_record.Incident (),
                                       intersection.Normal ()));
    f = Multiply (f, bsdf_record.Bsdf ()) * cos_t / bsdf_record.Pdf () / q;

    // Ready to trace the incident direction.
    ray = Ray (intersection.Position (), bsdf_record.Incident ());
  }
  return l;
}
/*
// ---------------------------------------------------------------------------
*/
} // namespace niepce
