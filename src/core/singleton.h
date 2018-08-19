/*!
 * @file singleton.h
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#ifndef _SINGLETON_H_
#define _SINGLETON_H_
/*
// ---------------------------------------------------------------------------
*/
#include "niepce.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
class SingletonFinalizer
{
public:
  typedef void (*FinalizerFunc) ();

  static auto AddFinalizer(FinalizerFunc func) -> void;
  static auto Finalize () -> void;
};
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
class Singleton final
{
public:
  static auto Instance () -> T&
  {
    std::call_once (init_flag_, Create);
    assert (instance_);
    return *instance_;
  }

private:
  static auto Create () -> void
  {
    instance_ = new T;
    SingletonFinalizer::AddFinalizer (&Singleton<T>::Destroy);
  }

  static void Destroy()
  {
    delete instance_;
    instance_ = nullptr;
  }

  static std::once_flag init_flag_;
  static T* instance_;
};
/*
// ---------------------------------------------------------------------------
*/
template <typename T> std::once_flag Singleton<T>::init_flag_;
template <typename T> T* Singleton<T>::instance_ = nullptr;
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _SINGLETON_H_

