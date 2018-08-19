/*!
 * @file film_tile.h
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#ifndef _FILM_TILE_H_
#define _FILM_TILE_H_
/*
// ---------------------------------------------------------------------------
*/
#include "niepce.h"
#include "bounds2f.h"
#include "imageio.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
//! ----------------------------------------------------------------------------
//! @class FilmTile
//! @brief
//! @details
//! ----------------------------------------------------------------------------
class FilmTile : public ImageIO <Spectrum>
{
public:
  //! The default class constructor.
  FilmTile () = delete;

  //! The constructor needs bounds2.
  FilmTile (int tile_number, const Bounds2f& bound);

  //! The copy constructor of the class.
  FilmTile (const FilmTile& tile) = default;

  //! The move constructor of the class.
  FilmTile (FilmTile&& tile) = default;

  //! The default class destructor.
  virtual ~FilmTile () = default;

  //! The copy assignment operator of the class.
  auto operator = (const FilmTile& tile) -> FilmTile& = default;

  //! The move assignment operator of the class.
  auto operator = (FilmTile&& tile) -> FilmTile& = default;

public:
  /*!
   * @fn Bounds2f Bounds ()
   * @brief 
   * @return 
   * @exception none
   * @details
   */
  auto Bounds () const noexcept -> Bounds2f;

  /*!
   * @fn Point2f Min ()
   * @brief 
   * @return 
   * @exception none
   * @details
   */
  auto Min () const noexcept -> Point2f;

  /*!
   * @fn Point2f Max ()
   * @brief 
   * @return 
   * @exception none
   * @details
   */
  auto Max () const noexcept -> Point2f;

  /*!
   * @fn int TileNumber ()
   * @brief 
   * @return 
   * @exception none
   * @details
   */
  auto TileNumber () const noexcept -> int;

  /*!
   * @fn void ClearTileImage ()
   * @brief 
   * @param[in] 
   * @return 
   * @exception none
   * @details
   */
  auto ClearTileImage () noexcept -> void;

private:
  const int      tile_number_;
  const Bounds2f tile_bounds_;
}; // class FilmTile
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _FILM_TILE_H_
