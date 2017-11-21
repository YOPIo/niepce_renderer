#ifndef _PIXEL_H_
#define _PIXEL_H_
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
class Pixel
{
  /* Pixel constructors */
public:
  Pixel () = default;
  Pixel (Float r, Float g, Float b);


  /* Pixel destructor */
public:
  virtual ~Pixel () = default;


  /* Pixel public operators*/
public:
  Pixel (const Pixel&  pixel) = default;
  Pixel (      Pixel&& pixel) = default;

  auto operator = (const Pixel&  pixel) -> Pixel& = default;
  auto operator = (      Pixel&& pixel) -> Pixel& = default;

  auto operator [] (const size_t idx)       -> Float&;
  auto operator [] (const size_t idx) const -> Float;

  auto operator + (const Pixel& p) const -> Pixel;
  auto operator - (const Pixel& p) const -> Pixel;
  auto operator * (Float t)        const -> Pixel;
  auto operator / (Float t)        const -> Pixel;

  auto operator += (const Pixel& p) -> Pixel&;
  auto operator -= (const Pixel& p) -> Pixel&;
  auto operator *= (Float t) -> Pixel&;
  auto operator /= (Float t) -> Pixel&;

  /* Pixel public data */
public:
  union
  {
    struct { Float r_, g_, b_; };
    std::array <Float, 3> rgb_;
  };

}; // class Pixel
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _PIXEL_H_
