#pragma once
#include <algorithm>
#include <mutex>
#include <set>
#include <thread>

#include "executor.h"
#include "logger.h"

namespace CppUtils {
namespace Execution {
class ThreadPerTaskExecutor : public Executor {
 public:
  ThreadPerTaskExecutor();
  ~ThreadPerTaskExecutor();

  void Execute(const Task& task);

 private:
  std::set<std::thread::id> workers;

  std::mutex mx;
  std::condition_variable cv;
};
}  // namespace Execution
}  // namespace CppUtils
