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
class FilmTile
{
public:
  //! The default class constructor.
  FilmTile () = delete;

  //! The constructor needs bounds2.
  FilmTile (const Bounds2f& bound);

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

  /*!
   * @fn operator ()
   * @brief 
   * @details 
   * @return 
   * @exception none
   */
  auto operator () (unsigned int x, unsigned int y) const noexcept -> Spectrum;

public:
  /*!
   * @fn Spectrum At (unsigned)
   * @brief 
   * @param[in] x
   *    
   * @param[in] y
   *    
   * @return 
   * @exception none
   * @details
   */
  auto At (unsigned int x, unsigned int y) const -> Spectrum;

  /*!
   * @fn int Width ()
   * @brief 
   * @return 
   * @exception none
   * @details
   */
  auto Width () const noexcept -> unsigned int;

  /*!
   * @fn unsigned Height ()
   * @brief 
   * @param[in] 
   * @param[out] 
   * @return 
   * @exception none
   * @details
   */
  auto Height () const noexcept -> unsigned int;

  /*!
   * @fn Bounds2f Bounds ()
   * @brief 
   * @return 
   * @exception none
   * @details
   */
  auto Bounds () const noexcept -> Bounds2f;

  /*!
   * @fn void SetSpectrum (unsigned int, unsigned int)
   * @brief 
   * @param[in] x
   *    
   * @param[in] y
   *    
   * @return void
   * @exception none
   * @details
   */
  auto SetSpectrumAt (unsigned int x, unsigned int y, const Spectrum& s) -> void;

private:
  const Bounds2f tile_bounds_;
  std::vector <Spectrum> data_;
}; // class FilmTile
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _FILM_TILE_H_
