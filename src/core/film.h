#ifndef _FILM_H_
#define _FILM_H_
/*
// ---------------------------------------------------------------------------
*/
#include "niepce.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
class Film
{
  /* Film public data structure */
 public:
  struct Pixel
  {
    std::array <Float, 3> rgb_;
  };

  /* Film constructors */
 public:
  Film () = delete;
  Film (const std::string& filename, uint32_t width, uint32_t height);

  /* Film destructor */
 public:
  virtual ~Film () = default;


  /* Film public operators*/
 public:
  Film (const Film&  film) = default;
  Film (      Film&& film) = default;

  auto operator = (const Film&  film) -> Film& = default;
  auto operator = (      Film&& film) -> Film& = default;

  auto operator () (Index x, Index y) const -> Film::Pixel;
  auto operator () (Index x, Index y)       -> Film::Pixel&;


  /* Film public methods */
 public:
  auto At (Index x, Index y) const -> Film::Pixel;
  auto At (Index x, Index y)       -> Film::Pixel&;


  /* Film private data */
 private:
  std::string    fullpath_; // Default location to save images
  const uint32_t width_;
  const uint32_t height_;
  const Float    diagonal_;

  std::unique_ptr <Pixel []> pixels_;
}; // class Film
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _FILM_H_
