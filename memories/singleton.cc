#include "singleton.h"

namespace niepce
{

const  int kMaxFinalizerSize  = 256;
static int gNumFinalizersSize = 0;
static std::array<SingletonFinalizer::FinalizerFunc, kMaxFinalizerSize> gFinalizers;

auto SingletonFinalizer::AddFinalizer(FinalizerFunc func) -> void
{
  assert(gNumFinalizersSize < kMaxFinalizerSize);
  gFinalizers[gNumFinalizersSize++] = func;
}

auto SingletonFinalizer::Finalize() -> void
{
  for (int i = gNumFinalizersSize - 1; i >= 0; --i) { (*gFinalizers[i])(); }
  gNumFinalizersSize = 0;
}


}  // namespace niepce

