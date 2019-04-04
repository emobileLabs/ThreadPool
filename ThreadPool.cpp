
#include "ThreadPool.hpp"

namespace threadpool {

template <typename T, typename... Args>
std::unique_ptr<T> make_unique(Args &&... args) {
  return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

ThreadPool::ThreadPool(int threadCount)
    : taskQueue{std::make_shared<TaskQueue>()}, threadCount(threadCount) {
  for (int i = 0; i < threadCount; i++) {
    auto th = make_unique<TaskThread>(taskQueue);
    th->start();
    taskThreads.emplace_back(std::move(th));
  }
}

ThreadPool::~ThreadPool() { shutdown(); }

void ThreadPool::shutdown() {
  taskQueue->shutdown();
  taskThreads.clear();
}

bool ThreadPool::isShutdown() const { return taskQueue->isShutdown(); }
} // namespace threadpool