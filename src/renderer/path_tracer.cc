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
#include "../math/point3f.h"
#include "../math/vector3f.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
PathTracer::PathTracer (const RenderSettings& settings) :
  settings_ (settings),
  pool_     (settings.GetItem (RenderSettings::Item::kNumThread)),
  // pool_     (1),
  sampler_  (new RandomSampler ())
{}
/*
// ---------------------------------------------------------------------------
*/
auto PathTracer::Render (const Scene& scene) -> void
{
  scene_ = scene;
  // return ;

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

      std::cout << "[" << x << " " << y << "] "
                << "[" << x + tile_width << " " << y + tile_height << "]"
                << std::endl;;

      tile_bounds.push_back (tile);
    }
  }

  std::cout<< "The number of tiles " << tile_bounds.size() << std::endl;
  // Generate sampler for each tile.
  std::vector <std::unique_ptr <RandomSampler>> samplers;
  for (const auto& tile : tile_bounds)
  {
    const auto x = tile.Max ().X ();
    const auto y = tile.Min ().Y ();
    samplers.push_back (sampler_->Clone (y * tile_width + x));
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
    futures.emplace_back (pool_.Enqueue (func, tile_bounds[i], samplers[i].get ()));

    /*
    This is bug codes.
    auto task = [&] () { this->TraceRay (tile_bounds[i], samplers[i].get ()); };
    futures.emplace_back (pool_.Enqueue (task));
    */
  }
  std::cout << "The number of tasks " << futures.size() << std::endl;
  // Wait for all task done.
  for (auto& future : futures)
  {
    future.wait ();
  }
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
  Ray cam (Point3f(50,52,295.6), Normalize (Vector3f(0,-0.042612,-1)));
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
            r =  r + Contribution (ray, tile_sampler, 0) * (1.0 / (Float)num_sample);
          }
          image_[idx] = image_[idx]
                      + Vector3f (Clamp(r.X ()), Clamp(r.Y ()), Clamp(r.Z ()))
                      * 0.25;
        }
      }
    }
  }
}
/*
// ---------------------------------------------------------------------------
*/
auto PathTracer::Contribution
(
 const Ray& ray,
 RandomSampler* tile_sampler,
 unsigned int depth
)
  -> Vector3f
{
  // Intersect test.
  Intersection intersection;
  if (!scene_.IsIntersect (ray, &intersection))
  {
    // No intersection found.
    return Vector3f::Zero ();
  }

  const std::shared_ptr <Material> material = intersection.Material ();
  Vector3f f = material->color;

  // return f;

  const Float p = std::max (intersection.Material ()->color.X (),
                            std::max (intersection.Material ()->color.Y (),
                                      intersection.Material ()->color.Z ()) );
  if (++depth > 5)
  {
    if (tile_sampler->SampleFloat () < p)
    {
      f = f * (1.0 / p);
    }
    else
    {
      return intersection.Material ()->emittion;
    }
  }

  const Vector3f normal = Dot (intersection.Normal (), ray.Direction ()) < 0 ? intersection.Normal() : -intersection.Normal();
  // const Vector3f normal = -intersection.Normal ();

  if (material->type_ == Material::kDiffuse)
  {
    const Float r1  = 2.0 * kPi * tile_sampler->SampleFloat ();
    const Float r2  = tile_sampler->SampleFloat ();
    const Float r2s = std::sqrt (r2);

    const Float tx = r2s * std::cos (r1);
    const Float ty = r2s * std::sin (r1);
    const Float tz = std::sqrt (1 - r2);

    /*
    const Float tz     = sampler.SampleFloat();
    const Float phi    = sampler.SampleFloat() * 2.0 * kPi;
    const Float k      = sqrt(1.0 - tz * tz);
    const Float tx     = k * cos(phi);
    const Float ty     = k * sin(phi);
    */

    Vector3f tangent, binormal;
    BuildOrthonormalBasis (normal, &tangent, &binormal);

    const Vector3f d = tangent * tx + binormal * ty + normal * tz;

    return material->emittion
      + Multiply (f, Contribution(Ray (intersection.Position (), Normalize (d)),
                                  tile_sampler,
                                  depth));
  }
  else if (material->type_ == Material::kSpecular)
  {
    Vector3f d = ray.Direction() - normal * 2.0 * Dot (normal, ray.Direction());
    return material->emittion
      + Multiply (f, Contribution(Ray (intersection.Position(), Normalize (d)),
                                  tile_sampler,
                                  depth));
  }
  /*
  else
  {
    Ray reflect (intersection.Position (),
                 ray.Direction() - intersection.Normal() * 2.0 * Dot (intersection.Normal(), ray.Direction()));
    Vector3f nl = Dot (intersection.Normal (), ray.Direction ()) < 0
                ? intersection.Normal() : -intersection.Normal ();
    bool is_into = Dot (intersection.Normal (), nl) > 0;
    Float nc = 1.0;
    Float nt = 1.5;
    Float nnt = is_into ? nc / nt : nt / nc;
    Float ddn = Dot (ray.Direction (), nl);
    Float cos2t = 1 - nnt * nnt * (1.0 - ddn * ddn);
    if (cos2t < 0)
    {
      return material->emittion + Multiply(f, Contribution(reflect, tile_sampler, depth));
    }
    Vector3f tdir = (ray.Direction() * nnt - intersection.Normal ()
                     * ((is_into ? 1 : -1) * (ddn * nnt + std::sqrt (cos2t)))).Normalize ();
    Float a  = nt - nc;
    Float b  = nt + nc;
    Float R0 = a * a / (b * b);
    Float c  = 1 - (is_into ? -ddn : Dot (tdir, intersection.Normal ()));
    Float Re = R0 + (1 - R0) * c * c * c * c * c;
    Float Tr = 1 - Re;
    Float P  = 0.25 + 0.5 * Re;
    Float RP = Re / P;
    Float TP = Tr / (1 - P);
    return material->emittion + Multiply(f, depth > 2 ?
           (rng_.Next01 () < P ?
            Contribution(reflect, tile_sampler, depth) * RP
            : Contribution(Ray (intersection.Position (), tdir), tile_sampler, depth) * TP)
            : Contribution(reflect, tile_sampler, depth) * Re
              + Contribution(Ray (intersection.Position (), tdir), tile_sampler, depth) * Tr);
  }
  */
}
/*
// ---------------------------------------------------------------------------
*/
} // namespace niepce
