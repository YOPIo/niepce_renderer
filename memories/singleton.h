#ifndef _SINGLETOH_H_
#define _SINGLETOH_H_

#include <cassert>
#include <mutex>

namespace niepce
{

// mozc singleton pattern
// http://qiita.com/kikuuuty/items/fcf5f7df2f0493c437dc
class SingletonFinalizer
{
 public:
  typedef void(*FinalizerFunc)();

  static auto AddFinalizer(FinalizerFunc func) -> void;
  static auto Finalize()                       -> void;
}; // class SingletonFinalizer

template <typename T>
class Singleton final
{
  // ---------------------------------------------------------------------------
  // Singleton public method
  // ---------------------------------------------------------------------------
 public:
  static auto GetInstance() -> T&
  {
    std::call_once(init_flag_, Init);
    assert(instance_);
    return *instance_;
  }


  // ---------------------------------------------------------------------------
  // Singleton private methods
  // ---------------------------------------------------------------------------
 private:
  static auto Init() -> void
  {
    instance_ = new T;
    SingletonFinalizer::AddFinalizer(&Singleton<T>::Delete);
  }

  static auto Delete() -> void
  {
    delete instance_;
    instance_ = nullptr;
  }


  // ---------------------------------------------------------------------------
  // Singleton private static data
  // ---------------------------------------------------------------------------
 private:
  static std::once_flag init_flag_;
  static T*             instance_;
}; // class Singleton

template <typename T> std::once_flag Singleton<T>::init_flag_;
template <typename T> T* Singleton<T>::instance_ = nullptr;


}  // namespace niepce

#endif // _SINGLETOH_H_
