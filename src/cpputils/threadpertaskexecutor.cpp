#include "threadpertaskexecutor.h"

namespace CppUtils {
namespace Execution {
ThreadPerTaskExecutor::ThreadPerTaskExecutor() {}

ThreadPerTaskExecutor::~ThreadPerTaskExecutor() {
  auto lock = std::unique_lock<std::mutex>(mx);
  auto predicate = [this] { return workers.empty(); };

  cv.wait(lock, predicate);
}

void ThreadPerTaskExecutor::Execute(const Task& task) {
  std::thread([this, task] {
    auto threadID = std::this_thread::get_id();

    {
      auto lock = std::unique_lock<std::mutex>(mx);
      workers.emplace(threadID);
    }

    try {
      task();
    } catch (const std::exception& ex) {
      Logger::Warning("ThreadPerTaskExecutor caught exception: {}", ex.what());
    }

    {
      auto lock = std::unique_lock<std::mutex>(mx);
      workers.erase(threadID);

      cv.notify_all();
    }
  }).detach();
}
}  // namespace Execution
}  // namespace CppUtils
