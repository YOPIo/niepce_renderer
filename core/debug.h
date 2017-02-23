#ifndef _DEBUG_H_
#define _DEBUG_H_

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <stdlib.h>

#define Debugf(fmt, ...)               \
  fprintf(stderr, "\x1b[32m");         \
  fprintf(stderr, "[Debug] ");         \
  fprintf(stderr, fmt, ##__VA_ARGS__); \
  fprintf(stderr, "\n");               \
  fprintf(stderr, "\x1b[39m");

#define Warningf(exp, fmt, ...)                                         \
  if ((exp))                                                            \
  {                                                                     \
    fprintf(stderr, "\x1b[33m");                                        \
    fprintf(stderr, "[Warning] %s @%s: %u ", #exp, __FILE__, __LINE__); \
    fprintf(stderr, fmt, ##__VA_ARGS__);                                \
    fprintf(stderr, "\n");                                              \
    fprintf(stderr, "\x1b[39m");                                        \
  }

#ifdef ASSERT
  #define Assertf(exp, fmt, ...)                                            \
    if ((exp))                                                              \
    {                                                                       \
      fprintf(stderr, "\x1b[31m");                                          \
      fprintf(stderr, "[Assertion] %s @%s: %u ", #exp, __FILE__, __LINE__); \
      fprintf(stderr, fmt, ##__VA_ARGS__);                                  \
      fprintf(stderr, "\n");                                                \
      fprintf(stderr, "\x1b[39m");                                          \
      std::quick_exit(0);                                                   \
    }
#else  // ASSERT
  #define Assertf(exp, fmt, ...)                                            \
    if ((exp))                                                              \
    {                                                                       \
      fprintf(stderr, "\x1b[31m");                                          \
      fprintf(stderr, "[Assertion] %s @%s: %u ", #exp, __FILE__, __LINE__); \
      fprintf(stderr, fmt, ##__VA_ARGS__);                                  \
      fprintf(stderr, "\n");                                                \
      fprintf(stderr, "\x1b[39m");                                          \
    }
#endif // ASSERT

#endif // _DEBUG_H_
