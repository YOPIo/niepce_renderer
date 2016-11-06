#include "logger.h"

namespace niepce
{

auto Assert(const char* filename, int line, const char* message) -> void
{
  std::cerr.flush() << "\x1b[31m";
  std::cerr.flush() << "[Assertion] " << "File: " << filename << ", "
                    << "Line: " << line << ", " << message << "\n";
  std::cerr.flush() << "\x1b[39m";
  //std::quick_exit(EXIT_FAILURE);
  std::exit(0);
}

auto Halt(const char* filename, int line, const char* message) -> void
{
  std::cerr.flush() << "\x1b[31m";
  std::cerr.flush() << "[Halt] " << "File: " << filename << ", "
                    << "Line: " << line << ", " << message << "\n";
  std::cerr.flush() << "\x1b[39m";
  //std::quick_exit(EXIT_FAILURE);
  std::exit(0);
}

} // niepce
