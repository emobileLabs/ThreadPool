
#include "TaskQueue.hpp"

namespace threadpool {

TaskQueue::TaskQueue() : shutDown(false) {}

std::packaged_task<void()> TaskQueue::pop() {
  std::packaged_task<void()> pt;

  std::unique_lock<std::mutex> lock{mtx};
  auto isWait = [this]() { return shutDown || !queue.empty(); };
  if (!isWait()) {
    CV.wait(lock, isWait);
  }

  if (!queue.empty()) {
    pt = std::move(queue.front());
    queue.pop_front();
  }
  return pt;
}

void TaskQueue::shutdown() {
  std::lock_guard<std::mutex> lk{mtx};
  queue.clear();
  shutDown = true;
  CV.notify_all();
}

bool TaskQueue::isShutdown() { return shutDown; }
} // namespace threadpool