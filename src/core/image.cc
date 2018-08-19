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
  data_   (new T [width * height], std::default_delete <T []> ())
{}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
Image<T>::~Image ()
{}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto Image<T>::operator () (unsigned int x, unsigned int y)
  const noexcept -> T
{
  if (y * width_ + x < width_ * height_)
  {
    return data_.get ()[y * width_ + x];
  }
  return data_.get ()[0];
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto Image<T>::At (unsigned int x, unsigned int y) const -> T
{
  if (y * width_ + x < width_ * height_)
  {
    return data_.get ()[y * width_ + x];
  }
  return data_.get ()[0];
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto Image<T>::SetValueAt
(
 unsigned int x,
 unsigned int y,
 const T& value
)
  const -> void
{
  if (y * width_ + x < width_ * height_)
  {
    data_.get ()[y * width_ + x] = value;
    return ;
  }
  std::cout << "out of range in image.cc" << std::endl;
  std::cout << x << ", " << y <<std::endl;
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto Image<T>::Height () const noexcept -> int
{
  return height_;
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto Image<T>::Width () const noexcept -> int
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
