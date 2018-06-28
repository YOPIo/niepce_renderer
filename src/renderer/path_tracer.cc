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
#include "../light/infinite_light.h"
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
  constexpr static int tile_size = 8;
  static int tile_number = 1;
  const auto resolution = camera_->Resolution ();
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
  int i = 1;
  for (const auto& tile : tiles)
  {
    // tile.SaveAs ((std::to_string(i++) + ".ppm").c_str ());
    camera_->AddFilmTile (tile);
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
  const Bounds2f& tile_bounds = tile->Bounds ();

  static constexpr int num_sample = 64;
  const Float width  = static_cast <Float> (camera_->Width ());
  const Float height = static_cast <Float> (camera_->Height ());

  auto func = [&] (int x, int y) -> void
  {
    auto super_sampling = [&] (int sx, int sy) -> void
    {
      Spectrum r (0);
      for (int s = 0; s < num_sample; ++s)
      {
        const Point2f pfilm (x + tile_bounds.Min ().X (),
                             y + tile_bounds.Min ().Y ());
        Float weight = 0;
        Ray ray;
        while (!weight)
        {
          CameraSample cs (pfilm, tile_sampler->SamplePoint2f ());
          weight = camera_->GenerateRay (cs, &ray);
        }
        r = r + Radiance (ray, tile_sampler) / (Float)num_sample;
      }
      const Spectrum s = tile->At (x, y) + Spectrum (Clamp (r. X ()),
                                                     Clamp (r. Y ()),
                                                     Clamp (r. Z ())) * 0.25;
      tile->SetValueAt (x, y, s);
    };
    For2 (super_sampling, 2, 2);
  };
  For2 (func, tile->Width (), tile->Height ());
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
      // return contribution;

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
      return contribution;
    }

    // Ready to generate the BSDWEIGHT.
    const auto material = intersection.Material ();

    if (material->HasEmission ())
    {
      contribution = contribution + weight
                   * material->Emission (intersection.Texcoord ());
    }


    // -------------------------------------------------------------------------
    // Generate BSDS.
    // -------------------------------------------------------------------------

    // Sample incident direction.
    BsdfRecord bsdf_record (intersection);
    auto bsdf = material->AllocateBsdfs (intersection, &memory);

    const Vector3f incident
      = bsdf->Sample (&bsdf_record, tile_sampler->SamplePoint2f ());

    if (bsdf->Type () != BsdfType::kSpecular)
    {
      // NNE
    }

    weight = weight
           * bsdf_record.Bsdf () * bsdf_record.CosTheta () / bsdf_record.Pdf ();

    // -------------------------------------------------------------------------
    // Russian roulette
    // -------------------------------------------------------------------------
    Float q = std::fmax (contribution[0], std::fmax(contribution[1], contribution[2]));
    if (depth > 7)
    {
      if (tile_sampler->SampleFloat () >= q) { return contribution; }
    }
    else { q = 1.0; }

    // ---------------------------------------------------------------------------
    // Ready to trace the incident direction.
    // ---------------------------------------------------------------------------
    ray = Ray (intersection.Position (), incident);
  }

  return contribution;
}
/*
// ---------------------------------------------------------------------------
*/

/*
// ---------------------------------------------------------------------------
*/
} // namespace niepce
