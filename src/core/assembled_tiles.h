/*!
 * @file assembled_tiles.h
 * @brief 
 * @author Masashi Yoshida
 * @date 2018/4/30
 * @details 
 */
#ifndef _ASSEMBLED_TILES_H_
#define _ASSEMBLED_TILES_H_
/*
// ---------------------------------------------------------------------------
*/
#include "niepce.h"
#include "tile.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
//! ----------------------------------------------------------------------------
//! @class AssembledTiles
//! @brief The AssembledTiles class divide a image to some tiles.
//! @details
//! ----------------------------------------------------------------------------
class AssembledTiles
{
public:
  //! The default class constructor.
  /*!
   * Need to give parameters that resolution of rendering and each tile size.
   */
  AssembledTiles () = delete;

  //! The constructor takes the size of image and size of tile in std::pair
  AssembledTiles
  (
   const std::pair <unsigned int, unsigned int>& resolution,  // The resolution of rendering. (width/height)
   const std::pair <unsigned int, unsigned int>& tile_size    // The size of tile. (width/height)
  );

  //! The copy constructor of the class.
  AssembledTiles (const AssembledTiles& tiles) = default;

  //! The move constructor of the class.
  AssembledTiles (AssembledTiles&& tiles) = default;

  //! The default class destructor.
  virtual ~AssembledTiles () = default;

  //! The copy assignment operator of the class.
  auto operator = (const AssembledTiles& tiles) -> AssembledTiles& = default;

  //! The move assignment operator of the class.
  auto operator = (AssembledTiles&& tiles) -> AssembledTiles& = default;

public:
  /*!
   * @fn unsigned Height ()
   * @brief Return the height of resolution
   * @return The height as unsigned integer.
   * @exception none
   * @details
   */
  auto Height () const noexcept -> unsigned int;

  /*!
   * @fn unsigned Width ()
   * @brief Return the width of resolution.
   * @return The width as unsigned integer.
   * @exception none
   * @details
   */
  auto Width () const noexcept -> unsigned int;

  

private:
  /*!
   * @fn void GenerateTiles ()
   * @brief Generate tiles from resolution.
   * @param[in] Resolution
   * @param[in] Tile size
   * @return void
   * @exception none
   * @details Compute the each size of tile, If there is not enough width/height to generate tile image, some tiles will be smaller than specific size.
   */
  auto GenerateTiles
  (
   const std::pair <unsigned int, unsigned int>& resolution,
   const std::pair <unsigned int, unsigned int>& tile_size
  )
  noexcept -> void;


public:
  std::pair <unsigned int, unsigned int> resolution_;
  std::vector <Tile> tiles_;
}; // class AssembledTiles
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _ASSEMBLED_TILES_H_
