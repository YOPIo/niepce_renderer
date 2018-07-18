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
#include "../core/memory.h"
#include "../core/intersection.h"
#include "../core/point3f.h"
#include "../core/vector3f.h"
#include "../bsdf/bsdf.h"
#include "../bsdf/bsdf_record.h"
#include "../camera/camera.h"
#include "../core/singleton.h"
#include "../core/film_tile.h"
#include "../camera/camera_sample.h"
#include "../light/light.h"
#include "../light/area_light.h"
#include "../light/infinite_light.h"
#include "../sampler/hammersley.h"
#include "../sampler/low_discrepancy_sequence.h"
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
 const std::shared_ptr <Scene>&  scene,
 const std::shared_ptr <Camera>& camera
) :
  camera_ (camera),
  scene_  (scene)
{}
/*
// ---------------------------------------------------------------------------
*/
auto PathTracer::Render () -> void
{
  // Compute the tile bounds.
  std::vector <FilmTile> tiles;
  std::vector <std::shared_ptr <RandomSampler>> samplers;
  constexpr static int tile_size = 64;
  static int tile_number = 1;
  const auto resolution = camera_->FilmResolution ();
  const auto width  = resolution.Width ();
  const auto height = resolution.Height ();
  for (int y = 0; y < height; y += tile_size)
  {
    for (int x = 0; x < width; x += tile_size)
    {
      const int last_x = x + tile_size >= width  ? width  : x + tile_size;
      const int last_y = y + tile_size >= height ? height : y + tile_size;
      const Bounds2f tile (Point2f (x, y), Point2f (last_x, last_y));
      tiles.push_back (FilmTile (tile_number++, tile));
      // Clone sampler for each tile.
      samplers.push_back (std::make_shared <RandomSampler> (last_x * last_y));
    }
  }

  // Register the tasks
  ThreadPool& threads = Singleton <ThreadPool>::Instance ();
  std::vector <std::future <void>> futures (tiles.size ());
  for (int i = 0; i < tiles.size (); ++i)
  {
    auto func = std::bind (&PathTracer::RenderTileBounds,
                           this,
                           std::placeholders::_1,
                           std::placeholders::_2);
    futures[i] = threads.Enqueue (func,
                                  &tiles[i],
                                  samplers[i].get ());
  }

  // Wait for all task done.
  for (auto& future : futures) { future.wait (); }

  // Merge tiles
  for (const auto& tile : tiles)
  {
    // tile.SaveAs ((std::to_string(i++) + ".ppm").c_str ());
    camera_->UpdateFilmTile (tile);
  }

  camera_->Save ();
}
/*
// ---------------------------------------------------------------------------
*/
auto PathTracer::RenderTileBounds
(
 FilmTile*       tile,
 RandomSampler*  tile_sampler
)
  noexcept -> void
{
  int spp = 256;

  const auto &tile_bounds = tile->Bounds ();
  const auto begin_y = tile_bounds.Min ().Y ();
  const auto end_y   = tile_bounds.Max ().Y ();
  const auto begin_x = tile_bounds.Min ().X ();
  const auto end_x   = tile_bounds.Max ().X ();

  for (int s = 0; s < spp; ++s)
  {
    for (int y = begin_y; y < end_y; ++y)
    {
      for (int x = begin_x; x < end_x; ++x)
      {
        // TODO : Use better sampling.
        const auto offset = Point2f ((Float)s / spp, RadicalInverse (2, s));
        const auto pfilm = Point2f (x, y) + offset;
        const auto plens = tile_sampler->SamplePoint2f ();
        const auto cs    = CameraSample (pfilm, plens);

        Ray ray;
        const auto weight = camera_->GenerateRay (cs, &ray);

        Spectrum radiance;
        auto hit = Radiance (ray, tile_sampler, &radiance);

        auto s = tile->At (x - begin_x, y - begin_y) + radiance / (Float)spp;
        tile->SetValueAt (x - begin_x, y - begin_y, s);
      }
    }
  }

  /*
  const auto& tile_bounds = tile->Bounds ();
  static constexpr int num_sample = 64;
  const auto resolution = camera_->FilmResolution ();
  const Float width  = static_cast <Float> (resolution.Width ());
  const Float height = static_cast <Float> (resolution.Height ());

  auto func = [&] (int x, int y) -> void
  {
    auto super_sampling = [&] (int sx, int sy) -> void
    {
      Float inv = 1.0 / (Float)num_sample;
      Spectrum r (0);
      bool hit = false;
      int tx, ty;
      for (int s = 0; s < num_sample; ++s)
      {
        const Point2f pfilm (x + tile_bounds.Min ().X (),
                             y + tile_bounds.Min ().Y ());
        tx = pfilm.X ();
        ty = pfilm.Y ();
        Float weight = 0;
        Ray ray;
        while (!weight)
        {
          CameraSample cs (pfilm, tile_sampler->SamplePoint2f ());
          weight = camera_->GenerateRay (cs, &ray);
        }
        Spectrum radiance;
        hit = Radiance (ray, tile_sampler, &radiance) | hit;
        r = r + radiance * inv;
      }
      if (hit)
      {
        const auto s = tile->At (x, y) + Spectrum (Clamp (r.X ()),
                                                   Clamp (r.Y ()),
                                                   Clamp (r.Z ())) * 0.25;
        tile->SetValueAt (x, y, s);
      }
      else
      {
        const auto s = camera_->Background (tx, ty);
        tile->SetValueAt (x, y, s);
      }
    };
    For2 (super_sampling, 2, 2);
  };
  For2 (func, tile->Width (), tile->Height ());
  */
}
/*
// ---------------------------------------------------------------------------
*/
auto PathTracer::Radiance
(
 const Ray     &first_ray,
 RandomSampler *tile_sampler,
 Spectrum      *radiance
)
  -> bool
{
  Spectrum contribution = Spectrum (0);
  Spectrum weight = Spectrum (1);

  Ray ray (first_ray);

  MemoryArena memory;

  // Render the tile.
  for (unsigned int depth = 0; depth < 10; ++depth)
  {
    // -------------------------------------------------------------------------
    // Intersection test
    // -------------------------------------------------------------------------

    // Intersect test.
    Intersection intersection;
    if (!scene_->IsIntersect (ray, &intersection))
    {
      // No intersection found.
      if (depth == 0)
      {
        return false;
      }

      // HACKME:
      intersection.SetOutgoing (-ray.Direction ());

      // Sample infinite light.
      const auto inf_light = scene_->InfiniteLight ();
      if (inf_light != nullptr)
      {
        Float pdf = 0;
        const auto s = inf_light->Evaluate (intersection, &pdf);
        contribution = contribution + weight * s;
      }
      break;
    }

    // If ray hit with light.
    // break soon.
    const auto& primitive = intersection.Primitive ();
    if (primitive->HasLight ())
    {
      // Hit light
      contribution = contribution + weight
                   * primitive->Light ()->Emission ();
      break;
    }

    // Generate BSDF.
    auto bsdf = intersection.Material ()->AllocateBsdfs (intersection, &memory);
    // -------------------------------------------------------------------------
    // Next Event Estimation (Direct light sampling)
    // -------------------------------------------------------------------------
    // if (depth > 1 && bsdf->Type () != BsdfType::kSpecular)
    {
      /*
      const auto value = DirectSampleOneLight (intersection,
                                               tile_sampler->SamplePoint2f ());
      if (value != Spectrum::Zero ())
      {
        BsdfRecord record (intersection);
        bsdf->Sample (&record, tile_sampler->SamplePoint2f ());
        contribution = contribution + weight * value * record.Bsdf ();
      }
      */
    }

    // Ready to generate the BSDF.
    const auto& material = intersection.Material ();
    if (material->HasEmission ())
    {
      contribution = contribution + weight
                   * material->Emission (intersection);
    }

    // -------------------------------------------------------------------------
    // BSDF sampling.
    // -------------------------------------------------------------------------
    // Sample incident direction.
    BsdfRecord bsdf_record (intersection);
    bsdf_record.SetSamplingTarget (niepce::Bxdf::Type::kAll);
    bsdf_record.SetOutgoing (-ray.Direction (), bsdf::Coordinate::kWorld);

    const auto f = bsdf->Sample (&bsdf_record, tile_sampler->SamplePoint2f ());

    if (bsdf_record.Pdf () == 0) { break; }

    weight = weight * bsdf_record.Bsdf () * bsdf_record.CosWeight ()
           / bsdf_record.Pdf ();

    // -------------------------------------------------------------------------
    // Russian roulette
    // -------------------------------------------------------------------------
    Float q = std::fmax (contribution[0],
                         std::fmax(contribution[1], contribution[2]));
    if (depth > 5)
    {
      if (tile_sampler->SampleFloat () >= q) { break; }
    }
    else { q = 1.0; }

    // -------------------------------------------------------------------------
    // Ready to trace the incident direction.
    // -------------------------------------------------------------------------
    const auto incident = bsdf_record.Incident (bsdf::Coordinate::kWorld);
    ray = Ray (intersection.Position (), incident);
  }

  *radiance = contribution;
  return true;
}
/*
// ---------------------------------------------------------------------------
*/
auto PathTracer::DirectSampleOneLight
(
 const Intersection& intersection,
 const Point2f&      sample
)
  const noexcept -> Spectrum
{
  // Choose one light in the scene.
  const auto idx = scene_->NumLight () * sample[0];
  const auto &light = scene_->Light (idx);

  // Sample on shape surface.
  const auto pos = light->SamplePosition (sample);

  // Get intersection point.
  const auto &ori = intersection.Position ();

  // Compute shadow ray direction.
  const Ray shadow_ray (intersection.Position (), (pos - ori));

  // Find obstacle.
  Intersection tmp;
  if (!scene_->IsIntersect (shadow_ray, &tmp))
  {
    // Unexpected case.
    // Shadow ray was not intersect with any shape.
    return Spectrum::Zero ();
  }

  // Compare the length
  static constexpr Float kShadowRayEpsilon = 0.001;
  const Float len = (pos - ori).Length ();
  const Float res = (tmp.Position () - ori).Length ();

  if (std::fabs (len - res) < kShadowRayEpsilon)
  {
    return light->Emission();
    // There was/were no obstacle(s) between intersection point and sampled
    // point on area light.
    const auto g = Dot (shadow_ray.Direction (), intersection.Normal ())
                 * Dot (-shadow_ray.Direction(), tmp.Normal ());
    return light->Emission () * g / light->Pdf ();
  }
  // Obstacle is exist.
  return Spectrum::Zero ();
}
/*
// ---------------------------------------------------------------------------
*/
} // namespace niepce
