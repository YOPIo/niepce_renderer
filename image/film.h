#ifndef _FILM_H_
#define _FILM_H_

#include <memory>
#include <utility>
#include <fstream>

#include "../core/common.h"

namespace niepce
{

class Film
{
 public:
  using Pixels = std::unique_ptr<Rgb[]>;

 public:
  Film();
  Film(const Size& size);
  Film(unsigned widht, unsigned height);
  virtual ~Film();

  Rgb& operator [] (std::size_t idx);

  Film(const Film& film) = default;
  Film(Film&& film)      = default;
  Film& operator = (const Film& film) = default;
  Film& operator = (Film&& film)      = default;

  auto Width() const -> unsigned;
  auto Height() const -> unsigned;

  auto SaveAs(const char* filename) const -> void;

 private:
  Pixels pixels_;
  Size   size_;
}; // class Film

}; // namespace nipce

#endif // _FILM_H_
