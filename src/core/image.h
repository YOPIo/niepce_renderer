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
//! @brief The fundamental core class that representing a image.
//! @details
//! ----------------------------------------------------------------------------
class Image
{
public:
  //! The default class constructor.
  Image ();

  //! The Constructor
  /*!
   * Use this constructor with width and height
   * Initialize with black
   */
  Image (unsigned int width, unsigned int height);

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
   * @fn Pixel operator ()
   * @brief Member access operator. (read only)
   * @details
   * @return Pixel
   * @exception std::out_of_range
   */
  auto operator () (unsigned int x, unsigned int y) const -> Pixel;

public:
  /*!
   * @fn unsigned Height ()
   * @brief Return the height of image size.
   * @return The height of image as unsigned integer.
   * @exception none
   * @details
   */
  auto Height () const noexcept -> unsigned int;

  /*!
   * @fn void SetPixel ()
   * @brief Set the pixel data to the specified coordinates in the internal image data.
   * @param[in] x coordinate
   * @param[in] y coordinate
   * @param[in] Pixel
   * @return void
   * @exception Throw the std::out_of_range exception if index over the range of size.
   * @details
   */
  auto SetPixel
  (
   unsigned int x, // X coordinate
   unsigned int y, // Y coordinate
   const Pixel& p  // Pixel
  )
  -> void;

  /*!
   * @fn unsigned Width ()
   * @brief Return the width of image size.
   * @return The width of image as unsigned integer.
   * @exception none
   * @details
   */
  auto Width () const noexcept -> unsigned int;

private:
  unsigned int width_;
  unsigned int height_;
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

