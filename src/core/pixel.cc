#include "pixel.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
Pixel::Pixel (Float r, Float g, Float b) :
  r_ (r), g_ (g), b_ (b)
{}
/*
// ---------------------------------------------------------------------------
*/
auto Pixel::operator [] (const size_t idx) -> Float&
{
  return rgb_[idx];
}
/*
// ---------------------------------------------------------------------------
*/
auto Pixel::operator [] (const size_t idx) const -> Float
{
  return rgb_[idx];
}
/*
// ---------------------------------------------------------------------------
*/
auto Pixel::operator + (const Pixel &p) const -> Pixel
{
  return Pixel (r_ + p.r_, g_ + p.g_, b_ + p.g_);
}
/*
// ---------------------------------------------------------------------------
*/
auto Pixel::operator - (const Pixel &p) const -> Pixel
{
  return Pixel (r_ - p.r_, g_ - p.g_, b_ - p.g_);
}
/*
// ---------------------------------------------------------------------------
*/
auto Pixel::operator * (Float t) const -> Pixel
{
  return Pixel (r_ * t, g_ * t, b_ * t);
}
/*
// ---------------------------------------------------------------------------
*/
auto Pixel::operator / (Float t) const -> Pixel
{
  return Pixel (r_ / t, g_ / t, b_ / t);
}
/*
// ---------------------------------------------------------------------------
*/
auto Pixel::operator += (const Pixel& p) -> Pixel&
{
  this->r_ += p.r_;
  this->g_ += p.g_;
  this->b_ += p.b_;
  return *this;
}
/*
// ---------------------------------------------------------------------------
*/
auto Pixel::operator -= (const Pixel& p) -> Pixel&
{
  this->r_ -= p.r_;
  this->g_ -= p.g_;
  this->b_ -= p.b_;
  return *this;
}
/*
// ---------------------------------------------------------------------------
*/
auto Pixel::operator *= (Float t) -> Pixel&
{
  this->r_ *= t;
  this->g_ *= t;
  this->b_ *= t;
  return *this;
}
/*
// ---------------------------------------------------------------------------
*/
auto Pixel::operator /= (Float t) -> Pixel&
{
  this->r_ /= t;
  this->g_ /= t;
  this->b_ /= t;
  return *this;
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
