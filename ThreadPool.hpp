/**
 *
 * @brief        This class implements thread pool pattern, to execute tasks
 *               asynchronously
 *
 */

#ifndef THREADPOOL_HPP
#define THREADPOOL_HPP

#include <memory>
#include <vector>

#include "TaskQueue.hpp"
#include "TaskThread.hpp"

namespace threadpool {

class ThreadPool {
public:
  ThreadPool(int threadCount = 0);
  ~ThreadPool();
  /**
   * Submit the task on the asynchronous executor thread
   *
   * @param[in] task      Task is a any Callable type (function, lambda
   *                      expression, bind or another function object) to be
   *                      executed
   * @param[in] args      suitable list of argument types
   *
   * @returns std::future to know the status, this is optional for the apps
   * to use it
   */
  template <typename F, typename... Args>
  auto submitTask(F task, Args &&... args)
      -> std::future<decltype(task(args...))>;

  /**
   * Clears the outstanding tasks and refuses additional task submissions
   */
  void shutdown();

  /**
   * returns status of shutdown
   */
  bool isShutdown() const;

private:
  // Queue of tasks
  std::shared_ptr<TaskQueue> taskQueue = nullptr;

  int threadCount;

  std::vector<std::unique_ptr<TaskThread>> taskThreads;
};

template <typename F, typename... Args>
auto ThreadPool::submitTask(F task, Args &&... args)
    -> std::future<decltype(task(args...))> {
  return taskQueue->push(task, std::forward<Args>(args)...);
}

} // namespace threadpool
#endif
