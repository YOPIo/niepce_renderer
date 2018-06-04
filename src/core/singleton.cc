/*!
 * @file singleton.cc
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#include "singleton.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
constexpr int kMaxFinalizersSize = 256;
static int num_finalizers = 0;
static SingletonFinalizer::FinalizerFunc finalizers[kMaxFinalizersSize];
/*
// ---------------------------------------------------------------------------
*/
auto SingletonFinalizer::AddFinalizer(FinalizerFunc func) -> void
{
  assert (num_finalizers < kMaxFinalizersSize);
  finalizers[num_finalizers++] = func;
}
/*
// ---------------------------------------------------------------------------
*/
auto SingletonFinalizer::Finalize () -> void
{
    for (int i = num_finalizers - 1; i >= 0; --i)
    {
        (*finalizers[i])();
    }
    num_finalizers = 0;
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
