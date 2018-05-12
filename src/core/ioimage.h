/*!
 * @file ioimage.h
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#ifndef _IOIMAGE_H_
#define _IOIMAGE_H_
/*
// ---------------------------------------------------------------------------
*/
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
//! @class IOImage
//! @brief
//! @details
//! ----------------------------------------------------------------------------
class IOImage : public Image
{
public:
  enum Format
  {
    kExr,
    kHdr,
    kPng,
    kTiff,
    kPpm
  };

public:
  //! The default class constructor.
  IOImage () = default;

  //! The Constructor load the file.
  IOImage (const char* filename);

  //! The copy constructor of the class.
  IOImage (const IOImage& image) = default;

  //! The move constructor of the class.
  IOImage (IOImage&& image) = default;

  //! The default class destructor.
  virtual ~IOImage () = default;

  //! The copy assignment operator of the class.
  auto operator = (const IOImage& image) -> IOImage& = default;

  //! The move assignment operator of the class.
  auto operator = (IOImage&& image) -> IOImage& = default;

public:
  /*!
   * @fn operator ()
   * @brief 
   * @details 
   * @param [in] x
   * @param [in] y
   * @return 
   * @exception none
   */
  auto operator () (unsigned int x, unsigned int y) const noexcept -> Pixel;

public:
  /*!
   * @fn Pixel At (unsigned)
   * @brief Return the pixel
   * @param[in] x
   * @param[in] y
   * @return Pixel
   * @exception none
   * @details
   */
  auto At (unsigned int x, unsigned int y) const -> Pixel;

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
   * @brief Save the image with argument format.
   * @param[in] format
   * @return void
   * @exception none
   * @details
   */
  auto Save (Format format) const noexcept -> void;

  /*!
   * @fn void SaveAs (const)
   * @brief Save the image.
   * @param[in] format
   * @return 
   * @exception none
   * @details
   */
  auto SaveAs (const char* filename, Format format) const noexcept-> void;

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


private:
  std::string name_;

}; // class IOImage
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _IOIMAGE_H_
