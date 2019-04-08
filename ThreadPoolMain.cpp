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

using resultCb = std::function<void(int result)>;
void resultCallback(int res) {
  std::cout<<" Result Callback output: "<<res<<'\n';
}

void add(int a, int b, resultCb cb) {
  if(cb) {
    cb(a+b);
  }
}

// Main subroutine
int main() {
  std::cout << " main\n";
  std::shared_ptr<ThreadPool> tp;
  int threadSize = 1;
  tp = std::make_shared<ThreadPool>(threadSize);

  // Simple std::function 
  std::function<void()> func = []() { std::cout << "Inside function\n"; };
  tp->submitTask(func);

  // bind function with callback
  tp->submitTask(std::bind(&add, 10,10, &resultCallback));

  std::string input;
  std::cout << " Press ENTER to exit\n";
  std::getline(std::cin, input);
  return 0;
}