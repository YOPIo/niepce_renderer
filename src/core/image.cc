/*!
 * @file image.h
 * @brief The fundamental class for image.
 * @author Masashi Yoshida
 * @date 2018/4/20
 * @details
 */
#include "image.h"
#include "vector3f.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
Image<T>::Image (unsigned int width, unsigned int height) :
  width_  (width),
  height_ (height),
  data_   (new T [width * height])
{}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto Image<T>::operator () (unsigned int x, unsigned int y)
  const noexcept -> T
{
  return data_[y * width_ + x];
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto Image<T>::At (unsigned int x, unsigned int y) const -> T
{
  if (width_ <= x || height_ <= y) { throw std::out_of_range (""); }
  return data_[y * width_ + x];
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto Image<T>::Height () const noexcept -> unsigned int
{
  return height_;
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto Image<T>::Width () const noexcept -> unsigned int
{
  return width_;
}
/*
// ---------------------------------------------------------------------------
*/
template class Image <bool>;
template class Image <Float>;
template class Image <Spectrum>;
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
