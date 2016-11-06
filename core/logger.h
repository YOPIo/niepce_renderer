#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <iostream>
#include <cstdio>
#include <cstdlib>

namespace niepce
{

auto Assert(const char* filename, int line, const char* message) -> void;
auto Halt(const char* filename, int line, const char* message) -> void;

} // niepce

// print debug information in green color
#define DEBUG(...)                \
  fprintf(stderr, "\x1b[32m");    \
  fprintf(stderr, "[Debug] ");    \
  fprintf(stderr, __VA_ARGS__);   \
  fprintf(stderr, "\n");          \
  fprintf(stderr, "\x1b[39m");

// print warning information in yellow color
#define WARNING(...)              \
  fprintf(stderr, "\x1b[33m");    \
  fprintf(stderr, "[Warning] ");  \
  fprintf(stderr, __VA_ARGS__);   \
  fprintf(stderr, "\n");          \
  fprintf(stderr, "\x1b[39m");

// print error information in red color, kill program
#define ERROR(...)                \
  fprintf(stderr, "\x1b[31m");    \
  fprintf(stderr, "[Error] ");    \
  fprintf(stderr, __VA_ARGS__);   \
  fprintf(stderr, "\n");          \
  fprintf(stderr, "\x1b[39m");    \
  std::exit(0);
  //  std::quick_exit(EXIT_FAILURE);

// print information, kill program
#define HALT(exp) { niepce::Halt(__FILE__, __LINE__, #exp); }

// if exp is false, kill program
#define ASSERT(exp) (!!(exp) || (niepce::Assert(__FILE__, __LINE__, #exp), 0))



#endif // _LOGGER_H_
