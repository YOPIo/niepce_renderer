/*!
 * @file path_tracer.h
 * @brief 
 * @author Masashi Yoshida
 * @date 2018/4/23
 * @details
 */
#ifndef _PATH_TRACER_H_
#define _PATH_TRACER_H_
/*
// ---------------------------------------------------------------------------
*/
#include "../core/niepce.h"
#include "../core/render_settings.h"
#include "../core/thread_pool.h"
#include "../core/vector3f.h" // TODO: Delete
#include "../random/xorshift.h"
#include "../scene/scene.h"
#include "../sampler/random_sampler.h"
#include "../camera/camera.h"
#include "../core/film_tile.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
//! ----------------------------------------------------------------------------
//! @class PathTracer
//! @brief
//! @details
//! ----------------------------------------------------------------------------
class PathTracer
{
public:
  //! Default constructor
  PathTracer () = delete;

  //! The constructor takes render settings.
  PathTracer
  (
   const std::shared_ptr <Scene>&  scene,
   const std::shared_ptr <Camera>& camera
  );

  //! Copy constructor
  PathTracer (const PathTracer& pt) = default;

  //! Move constructor
  PathTracer (PathTracer&& pt) = default;

  //! Destructor
  virtual ~PathTracer () = default;

  //! Copy assignment operator
  auto operator = (const PathTracer& pt) -> PathTracer& = default;

  //! Move assignment operator
  auto operator = (PathTracer&& pt) -> PathTracer& = default;

public:
  //! @fn  Render ()
  //! @brief 
  //! @param[in] 
  //! @param[out] 
  //! @return 
  //! @exception none
  //! @details 
  auto Render () -> void;

private:
  /*!
   * @fn void TraceRay (RandomSampler*)
   * @brief 
   * @param[in] 
   * @param[out] 
   * @return 
   * @exception none
   * @details
   */
  auto RenderTileBounds
  (
   FilmTile*       tile,
   RandomSampler*  tile_sampler
  )
  noexcept -> void;

  /*!
   * @fn Vector3f Contribution (const)
   * @brief 
   * @param[in] ray
   * @return 
   * @exception none
   * @details
   */
  auto Radiance
  (
   const Ray& ray,
   RandomSampler* sampler
  )
    -> Vector3f;

  /*!
   * @fn Spectrum SampleInfiniteLight ()
   * @brief 
   * @param[in] 
   * @param[out] 
   * @return 
   * @exception none
   * @details 
   */
  auto SampleInfiniteLight (Float* pdf) -> Spectrum;

private:
  /*!
   * @fn Spectrum DirectSampleOneLight ()
   * @brief 
   * @return 
   * @exception none
   * @details
   */
  auto DirectSampleOneLight
  (
   const Intersection& intersection,
   const Point2f&      sample
  )
    const noexcept -> Spectrum;

private:
  std::shared_ptr <Scene>  scene_;
  std::shared_ptr <Camera> camera_;
}; // class PathTracer
/*
// ---------------------------------------------------------------------------
*/
} // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _PATH_TRACER_H_
