/*!
 * @file film.h
 * @brief 
 * @author Masashi Yoshida
 * @date 2018/4/21
 * @details 
 */
#include "bounds2.h"
#include "clipping_film.h"
#include "film.h"
#include "pixel.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
Film::Film (uint32_t width, uint32_t height) :
  resolution_ (std::make_pair (width, height)),
  film_       (width, height)
{}
/*
// ---------------------------------------------------------------------------
*/
auto Film::OverrideWithClippingFilm (const ClippingFilm& cfilm) -> void
{
  // Get first indices of clipping film
  const auto bounds = cfilm.Bounds2 ();

  const auto first = bounds.Min ();
  const auto last  = bounds.Max ();

  const uint32_t first_x = first.X ();
  const uint32_t first_y = first.Y ();
  const uint32_t last_x  = last.X ();
  const uint32_t last_y  = last.Y ();

  for (uint32_t y = first_y; y <= last_y; ++y)
  {
    for (uint32_t x = first_x; x <= last_x; ++x)
    {
      try
      {
        film_ (x, y) = cfilm (x, y);
      }
      catch (const std::exception& e)
      {
        // todo: implement
      }
    }
  }

  return ;
}
/*
// ---------------------------------------------------------------------------
*/
} // namespace niepce
