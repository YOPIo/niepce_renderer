/*!
 * @file thread_tool.h
 * @brief 
 * @author Masashi Yoshida
 * @date 2018/4/28
 * @details 
 */
#ifndef _THREAD_POOL_H_
#define _THREAD_POOL_H_
/*
// ---------------------------------------------------------------------------
*/
#include "niepce.h"
#include "singleton.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
//! ----------------------------------------------------------------------------
//! @class ThreadPool
//! @brief
//! @details
//! ----------------------------------------------------------------------------
class ThreadPool
{
public:
  //! The constructor that takes number of thread.
  /*!
   * Create the number of threads given in argument if possible. Otherwise,
     it set the number of thread to one.
   */
  ThreadPool (unsigned int num_threads = std::thread::hardware_concurrency ());
  // ThreadPool (unsigned int num_thread = 1);

  //! Copy constructor
  ThreadPool (const ThreadPool& pool) = default;

  //! Move constructor
  ThreadPool (ThreadPool&& pool) = default;

  //! Destructor
  virtual ~ThreadPool ();

  //! Copy assignment operator
  auto operator = (const ThreadPool& pool) -> ThreadPool& = default;

  //! Move assignment operator
  auto operator = (ThreadPool&& pool) -> ThreadPool& = default;

public:
  //! @fn std::future <typename std::result_of <F (Args...)>> Enqueue ()
  //! @brief Add a task that work on threads.
  //! @param[in] Any type of function.
  //! @return The result of operation.
  //! @exception none
  //! @details
  template <class F, class ... Args>
  auto Enqueue (F&& func, Args&& ... args)
    -> std::future <typename std::result_of <F (Args ...)>::type>;

private:
  std::vector <std::thread> workers_;
  std::queue <std::function <void ()>> tasks_;

  std::mutex mutex_;
  std::condition_variable condition_;

  bool stop_;
}; // class ThreadPool
/*
// ---------------------------------------------------------------------------
*/
template <class F, class ... Args>
auto ThreadPool::Enqueue(F&& func, Args&& ... args)
  -> std::future <typename std::result_of <F (Args ...)>::type>
{
  // The return type of function given in first argument.
  using ReturnType = typename std::result_of <F(Args ...)>::type;

  auto task = std::make_shared <std::packaged_task <ReturnType ()>>
    (std::bind (std::forward<F> (func), std::forward<Args> (args) ...));

  std::future <ReturnType> result = task->get_future();
  // Manage tasks (Exclusion control)
  {
    // Get the lock.
    std::unique_lock <std::mutex> lock (mutex_);

    // Add the task into the end of internal vector if thread pool is
    // not stopping.
    if(stop_)
    {
      throw std::runtime_error("enqueue on stopped ThreadPool");
    }
    tasks_.emplace ([task] () { (*task) (); });
  }
  condition_.notify_one ();

  return result;
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _THREAD_POOL_H_
