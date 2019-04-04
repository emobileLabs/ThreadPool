/**
 *
 * @brief        This class implements thread pool pattern, to execute tasks
 *               asynchronously
 *
 */

#include <iostream>
#include <memory>
#include <string>

#include "ThreadPool.hpp"

using namespace threadpool;

int main() {
  std::cout << " main\n";
  std::shared_ptr<ThreadPool> tp;
  int threadSize = 1;
  tp = std::make_shared<ThreadPool>(threadSize);

  std::function<void()> func = []() { std::cout << "Inside function\n"; };

  tp->submitTask(func);

  std::string input;
  std::cout << " Press ENTER to exit\n";
  std::getline(std::cin, input);
  return 0;
}