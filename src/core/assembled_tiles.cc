/*!
 * @file assembled_tiles.cc
 * @brief 
 * @author Masashi Yoshida
 * @date 2018/4/20
 * @details 
 */
#include "assembled_tiles.h"
#include "tile.h"
#include "point2f.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
AssembledTiles::AssembledTiles
(
 const std::pair <unsigned int, unsigned int>& resolution,
 const std::pair <unsigned int, unsigned int>& tile_size
) :
  resolution_ (resolution)
{
  GenerateTiles (resolution, tile_size);
}
/*
// ---------------------------------------------------------------------------
*/
inline auto AssembledTiles::Height () const noexcept -> unsigned int
{
  return resolution_.second;
}
/*
// ---------------------------------------------------------------------------
*/
inline auto AssembledTiles::Width () const noexcept -> unsigned int
{
  return resolution_.first;
}
/*
// ---------------------------------------------------------------------------
*/
auto AssembledTiles::GenerateTiles
(
 const std::pair <unsigned int, unsigned int>& resolution,
 const std::pair <unsigned int, unsigned int>& tile_size
)
noexcept -> void
{
  const unsigned int resolution_width  = resolution.first;
  const unsigned int resolution_height = resolution.second;
  const unsigned int tile_width  = tile_size.first;
  const unsigned int tile_height = tile_size.second;

  // Compute the each size of tile, If there is not enough width/height to generate tile image, some tiles will be smaller than specific size.
  for (unsigned int y = 0; y < resolution_height; y += tile_height)
  {
    for (unsigned int x = 0; x < resolution_width; x += tile_width)
    {
      // Todo: Support any tile size.

      // Compute the position for tile.
      const Point2f  min (x, y);
      const Point2f  max (x + tile_width - 1, y + tile_height - 1);
      const Bounds2f area (min, max);

      // Generate a tile and store it to internal data.
      tiles_.push_back (Tile (area));
    }
  }
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
