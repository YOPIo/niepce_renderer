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
 const RenderSettings           &settings,
 const std::shared_ptr <Scene>  &scene,
 const std::shared_ptr <Camera> &camera
) :
  Renderer (settings),
  camera_  (camera),
  scene_   (scene)
{}
/*
// ---------------------------------------------------------------------------
*/
auto PathTracer::Render () -> void
{
  const int num_rounds  = settings_.GetItem (RenderSettings::Item::kNumRound);
  const int tile_width  = settings_.GetItem (RenderSettings::Item::kTileWidth);
  const int tile_height = settings_.GetItem (RenderSettings::Item::kTileHeight);
  std::vector <FilmTile> tiles;

  const auto &resolution = camera_->FilmResolution ();
  const auto &width  = resolution.Width ();
  const auto &height = resolution.Height ();

  std::vector <std::shared_ptr <RandomSampler>> samplers;
  for (int y = 0; y < height; y += tile_height)
  {
    for (int x = 0; x < width; x += tile_width)
    {
      const int last_x = x + tile_width  >= width  ? width  : x + tile_width;
      const int last_y = y + tile_height >= height ? height : y + tile_height;
      const Bounds2f tile (Point2f (x, y), Point2f (last_x, last_y));
      tiles.push_back (FilmTile (y * height + x, tile));
      samplers.push_back (std::make_shared <RandomSampler> (last_y + last_x));
    }
  }

  ThreadPool& tasks = Singleton <ThreadPool>::Instance ();

  std::vector <std::future <void>> futures (tiles.size () * num_rounds);

  for (int round = 1, idx = 0; round <= num_rounds; ++round)
  {
    // Render each tile.
    for (int i = 0; i < tiles.size (); ++i)
    {
      auto func = std::bind (&PathTracer::RenderTileBounds,
                             this,
                             std::placeholders::_1,
                             std::placeholders::_2,
                             std::placeholders::_3);
      futures[idx++] = tasks.Enqueue (func,
                                      round,
                                      &tiles[i],
                                      samplers[i].get ());
    }
  }

  const auto &spp = settings_.GetItem (RenderSettings::Item::kNumSamples);
  int round = 0;
  for (int i = 0; i < futures.size (); ++i)
  {
    // Show progressing.
    std::cerr << (float)i / futures.size () * 100.0 << " %               \r";

    round = i / tiles.size () + 1;

    if ((round != 1) && (i % tiles.size () == 0))
    {
      camera_->SaveSequence (round, spp * (round - 1));
    }

    // Waiting for rendering of a tile.
    futures[i].wait ();

    // Update film.
    camera_->UpdateFilmTile (tiles[i % tiles.size ()], round);
  }

  // Final process
  camera_->FinalProcess (round, spp * (round));
  camera_->Save ();
}
/*
// ---------------------------------------------------------------------------
*/
auto PathTracer::RenderTileBounds
(
 int            round,
 FilmTile*      tile,
 RandomSampler* tile_sampler
)
  noexcept -> void
{
  // const int  spp = settings_.GetItem (RenderSettings::kNumSamples);
  const int spp = settings_.GetItem (RenderSettings::Item::kNumSamples);
  const auto tile_bounds = tile->Bounds ();
  const auto begin_y = static_cast <int> (tile_bounds.Min ().Y ());
  const auto end_y   = static_cast <int> (tile_bounds.Max ().Y ());
  const auto begin_x = static_cast <int> (tile_bounds.Min ().X ());
  const auto end_x   = static_cast <int> (tile_bounds.Max ().X ());

  for (int s = round * spp; s < round * spp + spp; ++s)
  {
    for (int y = begin_y; y < end_y; ++y)
    {
      for (int x = begin_x; x < end_x; ++x)
      {
        // TODO : Use better sampling.
        Ray ray;
        Float weight = 0;
        const auto offset = Point2f ((Float)s / (round * spp),
                                     RadicalInverse (2, s));
        // const auto pfilm  = Point2f (x, y) + offset;
        const auto pfilm  = Point2f (x, y) + tile_sampler->SamplePoint2f ();
        while (weight == 0)
        {
          const auto plens  = tile_sampler->SamplePoint2f ();
          const auto cs     = CameraSample (pfilm, plens);
          weight = camera_->GenerateRay (cs, &ray);
        }

        Spectrum radiance;
        auto hit = Radiance (ray, tile_sampler, &radiance);
        auto s = tile->At (x - begin_x, y - begin_y) + radiance;
        tile->SetValueAt (x - begin_x, y - begin_y, s);
      }
    }
  }
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

  const auto kMaxDepth = settings_.GetItem (RenderSettings::Item::kPTMaxDepth);

  // Render the tile.
  for (unsigned int depth = 0; depth < kMaxDepth; ++depth)
  {
    // -------------------------------------------------------------------------
    // Intersection test
    // -------------------------------------------------------------------------

    // Intersect test.
    Intersection intersection;
    if (!scene_->IsIntersect (ray, &intersection))
    {
      // No intersection found.
      /*
      if (depth == 0)
      {
        return false;
      }
      */

      // HACKME:
      intersection.SetOutgoing (-ray.Direction ());

      // Sample infinite light.
      const auto& inf_light = scene_->InfiniteLight ();
      if (inf_light != nullptr)
      {
        Float pdf = 0;
        const auto s = inf_light->Evaluate (intersection, &pdf);
        contribution = contribution + weight * s;
      }
      break;
    }

    // contribution = Normalize ((Spectrum (1) + intersection.Normal()) * 0.5);
    // break;

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
    const auto& material = intersection.Material ();
    if (material->HasEmission ())
    {
      contribution = contribution + weight
                   * material->Emission (intersection);
    }

    // -------------------------------------------------------------------------
    // BSDF sampling.
    // -------------------------------------------------------------------------
    // Ready for the sample incident direction and evaluating the BSDF.
    BsdfRecord bsdf_record (intersection);
    bsdf_record.SetSamplingTarget (niepce::Bxdf::Type::kAll);
    bsdf_record.SetOutgoing (-ray.Direction (), bsdf::Coordinate::kWorld);

    const auto f = bsdf->Sample (&bsdf_record, tile_sampler->SamplePoint2f ());

    if (bsdf_record.Pdf () == 0) { break; }

    // -------------------------------------------------------------------------
    // Next event estimation
    // -------------------------------------------------------------------------
    if ((bsdf_record.SampledType ()
         & Bsdf::Type (Bsdf::Type::kSpecular)) != Bsdf::Type::kSpecular)
    {
      const auto value = DirectSampleOneLight (intersection,
                                               tile_sampler->SamplePoint2f());
      if (value != Spectrum::Zero ())
      {
        contribution = contribution + weight * bsdf_record.Bsdf () * value;
      }
    }

    // Update the weight.
    weight = weight * bsdf_record.Bsdf () * bsdf_record.CosWeight ()
           / bsdf_record.Pdf ();

    // -------------------------------------------------------------------------
    // Russian roulette
    // -------------------------------------------------------------------------
    /*
    Float q = std::fmax (contribution[0],
                         std::fmax(contribution[1], contribution[2]));
    if (kMaxDepth - 3 > depth)
    {
      if (tile_sampler->SampleFloat () >= q) { break; }
    }
    else { q = 1.0; }
    */

    // -------------------------------------------------------------------------
    // Ready to trace the incident direction.
    // -------------------------------------------------------------------------
    const auto incident = bsdf_record.Incident (bsdf::Coordinate::kWorld);
    const auto origin = intersection.Position () + incident * 0.001;
    ray = Ray (origin, incident);
  }

  *radiance = contribution;
  return true;
}
/*
// ---------------------------------------------------------------------------
*/
auto PathTracer::DirectSampleOneLight
(
 const Intersection& isect,
 const Point2f&      sample
)
  const noexcept -> Spectrum
{
  // Choose one light in the scene.
  const auto num_lights = scene_->NumLight ();
  if (num_lights == 0)
  {
    return Spectrum (0);
  }

  auto idx = num_lights * sample[0];
  if (idx >= scene_->NumLight ()) { idx = scene_->NumLight () - 1; }
  const auto &light = scene_->Light (idx);

  // Sample a position on the light.
  const auto target = light->SamplePosition (sample);

  // Get intersection point.
  const auto &ori = isect.Position ();

  // Create shadow ray.
  const Ray shadow_ray (ori, (target - ori));

  // Find obstacle.
  Intersection tmp;
  if (!scene_->IsIntersect (shadow_ray, &tmp))
  {
    // Unexpected case.
    // Shadow ray was not intersect with any shape.
    // std::cerr << "In Pathtracer::DirectSampleOneLight" << std::endl;
    return Spectrum::Zero ();
  }

  // Compare the length
  static constexpr auto kShadowRayEpsilon = 0.1;
  const auto len = (target - ori).Length ();
  const auto res = (tmp.Position () - ori).Length ();

  if (std::fabs (len - res) < kShadowRayEpsilon)
  {
    const auto g = std::fabs (Dot (shadow_ray.Direction (), isect.Normal ()))
                 * std::fabs (Dot (-shadow_ray.Direction(), tmp.Normal ()))
                 / (target - ori).LengthSquared ();
    return light->Emission () * g / light->Pdf ();
  }
  // Obstacle object was found.
  return Spectrum::Zero ();
}
/*
// ---------------------------------------------------------------------------
*/
} // namespace niepce
