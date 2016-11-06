#include "path.h"

namespace niepce
{

namespace path
{

auto ParseExtension(const std::string& path) -> std::string
{
  std::size_t pos = path.find_last_of(".");
  return path.substr(pos);
}

} // namespace path

} // namespace niepce
