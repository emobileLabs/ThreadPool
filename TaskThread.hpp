/**
 *
 * @brief        This class implements thread pool pattern, to execute tasks
 *               asynchronously
 *
 */

#ifndef TASKTHREAD_HPP
#define TASKTHREAD_HPP

#include <atomic>
#include <memory>
#include <thread>

#include "TaskQueue.hpp"

namespace threadpool {

class TaskThread {
public:
  TaskThread(std::shared_ptr<TaskQueue> taskQueue);

  ~TaskThread();

  // Start executing tasks on the thread
  void start();

  // Check whether task thread is active or shutdown
  bool isShutdown();

private:
  void processTasks();

  // weak_ptr for the taskQueue, if task queue is not accessible there is
  // no need to execute tasks
  std::weak_ptr<TaskQueue> taskQueue;

  // flag to indicate stop execution
  std::atomic_bool shutDown;

  std::thread thread;
};
} // namespace threadpool

#endif