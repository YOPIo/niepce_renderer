#ifndef _IMAGE_H_
#define _IMAGE_H_
/*
// ---------------------------------------------------------------------------
*/
#include "niepce.h"
#include "geometry.h"
#include "pixel.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
template <class DataType>
class BaseImage
{
  /* BaseImage constructors */
public:
  BaseImage () = default;
  BaseImage (size_t width, size_t height) :
    resolution_ (width, height)
  {
    data_.reset (new Pixel <DataType> [resolution_.x * resolution_.y],
                 std::default_delete<Pixel <Spectrum> []> ());
  }


  /* BaseImage destructor */
public:
  virtual ~BaseImage () = default;


  /* BaseImage public operators*/
public:
  BaseImage (const BaseImage&  img) = default;
  BaseImage (      BaseImage&& img) = default;

  auto operator = (const BaseImage&  img) -> BaseImage& = default;
  auto operator = (      BaseImage&& img) -> BaseImage& = default;

  auto operator () (size_t x, size_t y) -> Pixel <DataType>&
  {
    return data_ [y * resolution_.x + x];
  }
  auto operator () (size_t x, size_t y) const -> Pixel <DataType>
  {
    return data_ [y * resolution_.x + x];
  }


  /* BaseImage public methods */
public:
  auto At (size_t x, size_t y) -> Pixel <DataType>&
  {
    return data_ [y * resolution_.x + x];
  }
  auto At (size_t x, size_t y) const -> Pixel <DataType>
  {
    return data_ [y * resolution_.x + x];
  }

  auto GetWidth () const -> uint32_t
  {
    return resolution_.x;
  }
  auto GetHeight () const -> uint32_t
  {
    return resolution_.y;
  }

  auto Resize (size_t x, size_t y) -> void
  {
    data_.reset (new Pixel <DataType> [x * y],
                 std::default_delete<Pixel <Spectrum> []> ());
  }


  /* BaseImage private data */
private:
  std::shared_ptr <Pixel <DataType> []> data_;
  Point2u32i resolution_;

}; // class BaseImage
/*
// ---------------------------------------------------------------------------
*/
auto LoadImage
(
 const std::string& filepath,
 uint32_t*          width,
 uint32_t*          height
)
-> Vector4f*;
/*
// ---------------------------------------------------------------------------
*/
auto LoadHdrImage
(
 const std::string& filepath,
 uint32_t*          width,
 uint32_t*          height
)
-> Vector4f*;
/*
// ---------------------------------------------------------------------------
*/
class Image
{
  /* Image constructors */
public:
  Image ();
  Image (const std::string& filepath);


  /* Image destructor */
public:
  virtual ~Image ();


  /* Image public operators*/
public:
  Image (const Image&  img) = default;
  Image (      Image&& img) = default;

  auto operator = (const Image&  img) -> Image& = default;
  auto operator = (      Image&& img) -> Image& = default;

  auto operator [] (std::size_t idx) const -> Spectrum
  {
    return image_[idx];
  }

  // Return the pixel value (u, v)
  auto operator () (const Point2i& uv) const -> Vector4f;

  // The parameter should be zero to one
  // Compute the (u, v) and return the value at the (u, v)
  auto operator () (const Point2f& uv) const -> Vector4f;


  /* Image public methods */
public:
  auto Load   (const std::string& filepath) -> bool;
  auto Width  () const -> uint32_t;
  auto Height () const -> uint32_t;


  /* Image protected data */
private:
  std::string filepath_;
  std::string filename_;

  std::unique_ptr<Vector4f[]> image_;
  Point2<uint32_t> resolution_;
}; // class Image
/*
// ---------------------------------------------------------------------------
*/
template <typename DataType>
auto CreateBaseImage (uint32_t width, uint32_t height) -> ImagePtr <DataType>;
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _IMAGE_H_
