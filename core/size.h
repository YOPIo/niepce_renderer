#ifndef _SIZE_H_
#define _SIZE_H_

#include <utility>

namespace niepce
{

class Size
{
 public:
  Size();
  Size(unsigned w, unsigned h);
  ~Size();

  Size(const Size& size) = default;
  Size(Size&& size)      = default;
  Size& operator = (const Size& size) = default;
  Size& operator = (Size&& size)      = default;

  auto Width() const -> unsigned;
  auto Height() const -> unsigned;

 protected:
  unsigned width_;
  unsigned height_;
};

} // namespace niepce

#endif // _SIZE_H_
