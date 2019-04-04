/**
 * @brief       This class contains queue of tasks to run
 */

#ifndef TASKQUEUE_HPP
#define TASKQUEUE_HPP

#include <atomic>
#include <condition_variable>
#include <deque>
#include <future>
#include <mutex>

namespace threadpool {

class TaskQueue {
public:
  TaskQueue();

  // push the task back of the queue
  template <typename F, typename... Args>
  auto push(F task, Args &&... args) -> std::future<decltype(task(args...))> {
    return pushTo(std::forward<F>(task), std::forward<Args>(args)...);
  }

  // pop first task from the queue
  std::packaged_task<void()> pop();

  // clears the outstanding tasks and refuses additional task submission
  void shutdown();

  // Check the status of shutdown
  bool isShutdown();

private:
  // Queue of tasks
  std::deque<std::packaged_task<void()>> queue;

  // mutex to protect queue
  std::mutex mtx;

  // A condition variable to wait for new tasks to be placed on the queue
  std::condition_variable CV;

  // flag for indicating whether to accept more tasks or not
  std::atomic_bool shutDown;

  template <typename F, typename... Args>
  auto pushTo(F task, Args &&... args) -> std::future<decltype(task(args...))>;
};

template <typename F, typename... Args>
auto TaskQueue::pushTo(F task, Args &&... args)
    -> std::future<decltype(task(args...))> {
  using returnType = decltype(task(args...));
  auto boundedTask =
      std::bind(std::forward<F>(task), std::forward<Args>(args)...);

  auto pkgedTask = std::packaged_task<returnType()>(boundedTask);
  auto future = pkgedTask.get_future();
  {
    std::lock_guard<std::mutex> lock(mtx);
    queue.emplace_back(std::move(pkgedTask));
  }
  CV.notify_one();
  return future;
}
} // namespace threadpool
#endif
