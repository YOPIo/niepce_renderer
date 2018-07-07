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
template <typename T>
class ImageTexture : public Texture <T>
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
   * @fn T Evaluate (const)
   * @brief 
   * @param[in] 
   * @return 
   * @exception none
   * @details 
   */
  auto Evaluate (const Intersection& isect) const noexcept -> T override final;

  /*!
   * @fn bool IsBlack ()
   * @brief 
   * @return 
   * @exception none
   * @details
   */
  auto IsBlack () const noexcept -> bool override final;

private:
  std::shared_ptr <ImageIO <T>> image_;
}; // class ImageTexture
/*
// ---------------------------------------------------------------------------
// Function for the image texture
// ---------------------------------------------------------------------------
*/
template <typename T>
auto CreateImageTexture (const Attributes &attrs)
  -> std::shared_ptr <Texture <T>>;
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _IMAGE_TEXTURE_H_

