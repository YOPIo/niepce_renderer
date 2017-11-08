#ifndef _IMAGE_H_
#define _IMAGE_H_
/*
// ---------------------------------------------------------------------------
*/
#include "niepce.h"
#include "geometry.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
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
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _IMAGE_H_
