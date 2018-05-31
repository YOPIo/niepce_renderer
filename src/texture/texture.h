/*!
 * @file texture.h
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#ifndef _TEXTURE_H_
#define _TEXTURE_H_
/*
// ---------------------------------------------------------------------------
*/
#include "../core/niepce.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
//! ----------------------------------------------------------------------------
//! @class Texture
//! @brief
//! @details
//! ----------------------------------------------------------------------------
class Texture
{
public:
  //! The default class constructor.
  Texture () = default;

  //! The copy constructor of the class.
  Texture (const Texture& texture) = default;

  //! The move constructor of the class.
  Texture (Texture&& texture) = default;

  //! The default class destructor.
  virtual ~Texture () = default;

  //! The copy assignment operator of the class.
  auto operator = (const Texture& texture) -> Texture& = default;

  //! The move assignment operator of the class.
  auto operator = (Texture&& texture) -> Texture& = default;

public:
  /*!
   * @fn Spectrum Sample (Float)
   * @brief Sample the pixel.
   * @param[in] uv
   *    UV-parameter [0, 1]
   * @return Pixel
   * @exception none
   * @details
   */
  virtual auto Sample (const Point2f& uv) const noexcept -> Vector3f = 0;

}; // class Texture
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _TEXTURE_H_
