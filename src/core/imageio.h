/*!
 * @file ioimage.h
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#ifndef _IMAGEIO_H_
#define _IMAGEIO_H_
/*
// ---------------------------------------------------------------------------
*/
#include "niepce.h"
#include "image.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
//! ----------------------------------------------------------------------------
//! @class ImageIO
//! @brief
//! @details
//! ----------------------------------------------------------------------------
template <typename T>
class ImageIO : public Image <T>
{
public:
  //! The default class constructor.
  ImageIO () = delete;

  //! The constructor takes width and height.
  ImageIO (unsigned int width, unsigned int height);

  //! The construcoor takes width, hegith and filename.
  ImageIO (const char* filename, unsigned int width, unsigned int height);

  //! The Constructor load the file.
  ImageIO (const char* filename);

  //! The copy constructor of the class.
  ImageIO (const ImageIO& image) = default;

  //! The move constructor of the class.
  ImageIO (ImageIO&& image) = default;

  //! The default class destructor.
  virtual ~ImageIO ();

  //! The copy assignment operator of the class.
  auto operator = (const ImageIO& image) -> ImageIO& = default;

  //! The move assignment operator of the class.
  auto operator = (ImageIO&& image) -> ImageIO& = default;

public:
  /*!
   * @fn void Load (const)
   * @brief Load the image file via stb library.
   * @param[in] filename
   * @return 
   * @exception none
   * @details
   */
  auto Load (const char* filename) -> void;

  /*!
   * @fn void Save ()
   * @brief 
   * @param[in] 
   * @param[out] 
   * @return 
   * @exception none
   * @details
   */
  auto Save () const noexcept -> void;

  /*!
   * @fn void SaveAs (const)
   * @brief Save the image.
   * @param[in] format
   * @return 
   * @exception none
   * @details
   */
  auto SaveAs (const char* filename) const noexcept-> void;

  /*!
   * @fn Return Rename (std)
   * @brief Change the name.
   * @param[in] std::string
   * @return void
   * @exception none
   * @details
   */
  auto Rename (const std::string& new_name) noexcept -> void;

private:
  /*!
   * @fn void SavePng (const)
   * @brief Save PNG format image.
   * @param[in] filename
   * @return 
   * @exception none
   * @details
   */
  auto SavePng (const char* filename) const noexcept -> void;

  /*!
   * @fn void SaveHdr (const)
   * @brief Save HDR format image.
   * @param[in] filename
   * @return void
   * @exception none
   * @details
   */
  auto SaveHdr (const char* filename) const noexcept -> void;

  /*!
   * @fn void SavePpm (const)
   * @brief Save PPM format image.
   * @param[in] filename
   * @return void
   * @exception none
   * @details
   */
  auto SavePpm (const char* filename) const noexcept -> void;

  /*!
   * @fn  AllocateMemory ()
   * @brief Free memory and reallocate the memory.
   * @param[in] width
   * @param[in] height
   * @return void
   * @exception none
   * @details
   */
  auto AllocateMemory (unsigned int width, unsigned int height) -> void;

protected:
  std::string name_;
}; // class ImageIO
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _IOIMAGE_H_
