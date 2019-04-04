#include <iostream>

#include "TaskThread.hpp"

namespace threadpool {

TaskThread::TaskThread(std::shared_ptr<TaskQueue> taskQueue)
    : taskQueue(taskQueue), shutDown(false) {}

TaskThread::~TaskThread() {
  shutDown = true;
  if (thread.joinable()) {
    thread.join();
  }
}

void TaskThread::start() {
  thread = std::thread{[=] { processTasks(); }};
}

bool TaskThread::isShutdown() { return shutDown; }

void TaskThread::processTasks() {
  while (!shutDown) {
    auto tq = taskQueue.lock();
    if (tq && !tq->isShutdown()) {
      auto task = tq->pop();
      if (task.valid()) {
        task();
      } else {
        // std::cout<<" Unable to process task\n";
      }
    } else {
      // taskQueue is not available or destroyed killing the thread
      shutDown = true;
    }
  }
}

} // namespace threadpool