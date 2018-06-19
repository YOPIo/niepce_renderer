/*!
 * @file image_texture.h
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#ifndef _IMAGE_TEXTURE_H_
#define _IMAGE_TEXTURE_H_
/*
// ---------------------------------------------------------------------------
*/
#include "texture.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
//! ----------------------------------------------------------------------------
//! @class ImageTexture
//! @brief
//! @details
//! ----------------------------------------------------------------------------
class ImageTexture : public Texture
{
public:
  //! The default class constructor.
  ImageTexture () = default;

  //! The constructor takes filename.
  ImageTexture (const char* filename);

  //! The copy constructor of the class.
  ImageTexture (const ImageTexture& texture) = default;

  //! The move constructor of the class.
  ImageTexture (ImageTexture&& texture) = default;

  //! The default class destructor.
  virtual ~ImageTexture () = default;

  //! The copy assignment operator of the class.
  auto operator = (const ImageTexture& texture) -> ImageTexture& = default;

  //! The move assignment operator of the class.
  auto operator = (ImageTexture&& texture) -> ImageTexture& = default;

public:
  /*!
   * @fn Pixel Sample (Float)
   * @brief Sample the pixel.
   * @param[in] uv
   *    UV-parameter [0, 1]
   * @return Pixel
   * @exception none
   * @details
   */
  auto Sample (const Point2f& uv) const noexcept -> Spectrum override final;

  /*!
   * @fn bool IsBlack ()
   * @brief 
   * @return 
   * @exception none
   * @details
   */
  auto IsBlack () const noexcept -> bool override final;

private:
  std::shared_ptr <ImageIO <Spectrum>> image_;
}; // class ImageTexture
/*
// ---------------------------------------------------------------------------
// Function for the image texture
// ---------------------------------------------------------------------------
*/
auto CreateImageTexture (const std::string& filename) -> Texture*;
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _IMAGE_TEXTURE_H_

