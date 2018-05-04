/*!
 * @file tile.h
 * @brief 
 * @author Masashi Yoshida
 * @date 2018/4/29
 * @details 
 */
#ifndef _TILE_H_
#define _TILE_H_
/*
// ---------------------------------------------------------------------------
*/
#include "niepce.h"
#include "bounds2f.h"
#include "image.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
//! ----------------------------------------------------------------------------
//! @class Tile
//! @brief The tile class is used for specification the range of rendering.
//! @details 
//! ----------------------------------------------------------------------------
class Tile
{
public:
  //! The default class constructor.
  Tile () = default;

  //! The constructor takes argument representing area where renderer are going to render.
  Tile (const Bounds2f& bounds);

  //! The copy constructor of the class.
  Tile (const Tile& tile) = default;

  //! The move constructor of the class.
  Tile (Tile&& tile) = default;

  //! The default class destructor.
  virtual ~Tile () = default;

  //! The copy assignment operator of the class.
  auto operator = (const Tile& tile) -> Tile& = default;

  //! The move assignment operator of the class.
  auto operator = (Tile&& tile) -> Tile& = default;

public:
  /*!
   * @fn unsigned Height ()
   * @brief Return the height of image.
   * @return Height of image as unsigned integer.
   * @exception Throw the std::out_of_range exception if index over the height.
   * @details 
   */
  auto Height () const -> unsigned int;

  /*!
   * @fn Bounds2f RenderingArea ()
   * @brief Get the 2-dimensional bounding box that representing rendering area.
   * @return Bounds2f
   * @exception none
   * @details 
   */
  auto RenderingArea () const noexcept -> Bounds2f;

  /*!
   * @fn unsigned int Width ()
   * @brief Return the width of image.
   * @return Width of image as unsigned integer.
   * @exception Throw the std::out_of_range exception if index over the width.
   * @details 
   */
  auto Width () const -> unsigned int;

private:
  Bounds2f bounds_;
  Image    image_;
}; // class Tile
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _TILE_H_
