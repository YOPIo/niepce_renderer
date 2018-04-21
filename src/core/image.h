/*!
 * @file image.h
 * @brief 
 * @author Masashi Yoshida
 * @date 2018/4/20
 * @details 
 */
#ifndef _IMAGE_H_
#define _IMAGE_H_
/*
// ---------------------------------------------------------------------------
*/
#include "niepce.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
//! ----------------------------------------------------------------------------
//! @class Image
//! @brief 
//! @details 
//! ----------------------------------------------------------------------------
class Image
{
public:
  //! The default class constructor.
  Image () = delete;

  //! The Constructor
  /*!
   * Use this constructor with width and height
   * Initialize with black
   */
  Image (uint32_t width, uint32_t height);

  //! The copy constructor of the class.
  Image (const Image& img) = default;

  //! The move constructor of the class.
  Image (Image&& img) = default;

  //! The default class destructor.
  virtual ~Image () = default;

  //! The copy assignment operator of the class.
  auto operator = (const Image& img) -> Image& = default;

  //! The move assignment operator of the class.
  auto operator = (Image&& img) -> Image& = default;

  /*!
   * @fn operator ()
   * @brief Member access operator (read only)
   * @details 
   * @return Pixel
   * @exception std::out_of_range
   */
  auto operator () (int32_t x, int32_t y) const -> Pixel;

  /*!
   * @fn operator ()
   * @brief Member assignment operator (writable)
   * @details 
   * @return Pixel&
   * @exception std::out_of_range
   */
  auto operator () (int32_t x, int32_t y) -> Pixel&;

private:
  uint32_t width_;
  uint32_t height_;
  std::shared_ptr <Pixel []> pixels_;
}; // class Image
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _IMAGE_H_

