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
template <typename T>
class Image
{
public:
  //! The default class constructor.
  Image () = delete;

  //! The Constructor allocate memory.
  Image (unsigned int width, unsigned int height);

  //! The copy constructor of the class.
  Image (const Image& img) = default;

  //! The move constructor of the class.
  Image (Image&& img) = default;

  //! The default class destructor.
  virtual ~Image ();

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
  virtual auto operator () (unsigned int x, unsigned int y) const noexcept -> T;

public:
  /*!
   * @fn Specturm At (unsigned)
   * @brief 
   * @param[in] x
   *    x
   * @param[in] y
   *    y
   * @return 
   * @exception none
   * @details
   */
  virtual auto At (unsigned int x, unsigned int y) const -> T;

  /*!
   * @fn  SetValueAt (unsigned int, unsigned int, const T&)
   * @brief 
   * @param[in] x
   *    
   * @param[in] y
   *    
   * @param[in] value
   *    
   * @return 
   * @exception none
   * @details
   */
  virtual auto SetValueAt
  (
   unsigned int x,
   unsigned int y,
   const T& value
  )
  const -> void;


  /*!
   * @fn unsigned Height ()
   * @brief Return the height of image size.
   * @return The height of image as unsigned integer.
   * @exception none
   * @details
   */
  auto Height () const noexcept -> int;

  /*!
   * @fn unsigned Width ()
   * @brief Return the width of image size.
   * @return The width of image as unsigned integer.
   * @exception none
   * @details
   */
  auto Width () const noexcept -> int;

protected:
  int width_;
  int height_;
  std::shared_ptr <T> data_;
}; // class Image
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _IMAGE_H_
