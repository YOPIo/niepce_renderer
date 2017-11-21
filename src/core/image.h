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
// Class forward declaration
// ---------------------------------------------------------------------------
*/
class Image3f;
/*
// ---------------------------------------------------------------------------
// Functions for Image3f
// ---------------------------------------------------------------------------
*/
auto CreateImage3f (size_t width, size_t height) -> ImagePtr;
auto LoadImage     (const char* filename) -> ImagePtr;
auto LoadHdrxImage (const char* filename) -> ImagePtr;
/*
// ---------------------------------------------------------------------------
*/
class Image3f
{
  /* Image3f constructors */
public:
  Image3f () = default;
  Image3f (size_t width, size_t height);


  /* Image3f destructor */
public:
  virtual ~Image3f () = default;


  /* Image3f public operators*/
public:
  Image3f (const Image3f&  img) = default;
  Image3f (      Image3f&& img) = default;

  auto operator = (const Image3f&  img) -> Image3f& = default;
  auto operator = (      Image3f&& img) -> Image3f& = default;

  auto operator () (size_t x, size_t y)       -> Pixel&;
  auto operator () (size_t x, size_t y) const -> Pixel;


  /* Image3f public methods */
public:
  auto At (size_t x, size_t y)       -> Pixel&;
  auto At (size_t x, size_t y) const -> Pixel;

  auto GetWidth  () const -> uint32_t;
  auto GetHeight () const -> uint32_t;


  /* Image3f private data */
private:
  std::unique_ptr <Pixel []> data_;
  Point2u32i resolution_;
}; // class Image3f
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _IMAGE_H_
