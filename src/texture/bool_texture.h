/*!
 * @file bool_texture.h
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#ifndef _BOOL_TEXTURE_H_
#define _BOOL_TEXTURE_H_
/*
// ---------------------------------------------------------------------------
*/
#include "../core/niepce.h"
#include "texture.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
//! ----------------------------------------------------------------------------
//! @class BoolTexture
//! @brief
//! @details
//! ----------------------------------------------------------------------------
class BoolTexture final : public Texture
{
public:
  //! The default class constructor.
  BoolTexture () = default;

  //! The constructor takes file path.
  BoolTexture (const char* filename);

  //! The copy constructor of the class.
  BoolTexture (const BoolTexture& texture) = default;

  //! The move constructor of the class.
  BoolTexture (BoolTexture&& texture) = default;

  //! The default class destructor.
  virtual ~BoolTexture () = default;

  //! The copy assignment operator of the class.
  auto operator = (const BoolTexture& texture) -> BoolTexture& = default;

  //! The move assignment operator of the class.
  auto operator = (BoolTexture&& texture) -> BoolTexture& = default;

public:
  /*!
   * @fn Spectrum Sample (const Point2f&)
   * @brief Sample the pixel.
   * @param[in] uv
   *    UV-parameter [0, 1]
   * @return Pixel
   * @exception none
   * @details
   */
  auto Sample (const Point2f& uv) const noexcept -> Spectrum override final;

private:
  std::shared_ptr <ImageIO <bool>> image_;

}; // class BoolTexture
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _BOOL_TEXTURE_H_
