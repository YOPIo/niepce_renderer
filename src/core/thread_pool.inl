/*!
 * @file thread_pool.cc
 * @brief
 * @author Masashi Yoshida
 * @date 2018/4/28
 * @details
 */
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
inline ThreadPool::ThreadPool (uint32_t num_thread) :
  stop_ (false)
{
  auto run = [this] ()
  {
    while (true)
    {
      std::function <void ()> task;
      // Manage tasks (Exclusion control)
      {
        // Get lock of internal mutex.
        std::unique_lock <std::mutex> lock (this->mutex_);

        // Execute task if queue has tasks or need to stop thread pool.
        auto wait = [this] ()
        {
          return this->stop_ || !this->tasks_.empty ();
        };
        this->condition_.wait (lock, wait);

        // If there is no task in the queue, terminate the thread.
        if (this->stop_ && this->tasks_.empty ())
        {
          return ;
        }

        // Get a task from queue.
        task = std::move (this->tasks_.front ());
        // Remove a front task.
        this->tasks_.pop ();
      }

      // Operate the task
      task ();
    }
  }; // lambda

  // Ready for launching a worker thread.
  for (uint32_t t = 0; t < num_thread; ++t)
  {
    workers_.emplace_back (run);
  }
}
/*
// ---------------------------------------------------------------------------
*/
inline ThreadPool::~ThreadPool ()
{
  // Manage tasks (Exclusion control)
  {
    std::unique_lock <std::mutex> lock (mutex_);
    stop_ = true;
  }

  // Execute all tasks.
  condition_.notify_all ();

  // Join all threads.
  for (auto& w : workers_)
  {
    w.join ();
  }
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
