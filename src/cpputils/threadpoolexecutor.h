#pragma once
#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <stdexcept>
#include <thread>
#include <vector>

#include "executor.h"
#include "logger.h"

namespace CppUtils {
namespace Execution {
class ThreadPoolExecutor : public Executor {
 public:
  ThreadPoolExecutor(uint32_t nThreads);
  ~ThreadPoolExecutor();

  void Execute(const Task& task) override;

 private:
  void threadFunc();

 private:
  bool running;
  std::vector<std::thread> workers;
  std::queue<Task> tasks;
  std::mutex mx;
  std::condition_variable cv;
};
}  // namespace Execution
}  // namespace CppUtils
