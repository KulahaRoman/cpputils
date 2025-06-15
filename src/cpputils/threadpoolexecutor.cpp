#include "threadpoolexecutor.h"

namespace CppUtils {
namespace Execution {
ThreadPoolExecutor::ThreadPoolExecutor(
    uint32_t nThreads = std::thread::hardware_concurrency())
    : running(true) {
  for (auto i = 0u; i < nThreads; i++) {
    workers.emplace_back(std::thread(&ThreadPoolExecutor::threadFunc, this));
  }
}

ThreadPoolExecutor::~ThreadPoolExecutor() {
  {
    auto lock = std::unique_lock<std::mutex>(mx);
    running = false;

    cv.notify_all();
  }

  for (auto& worker : workers) {
    worker.join();
  }
}

void ThreadPoolExecutor::Execute(const Task& task) {
  auto lock = std::unique_lock<std::mutex>(mx);

  tasks.emplace(task);
  cv.notify_all();
}

void ThreadPoolExecutor::threadFunc() {
  while (true) {
    Task task;
    {
      auto lock = std::unique_lock<std::mutex>(mx);
      auto predicate = [this] { return !tasks.empty() || !running; };

      cv.wait(lock, predicate);

      if (!running) {
        break;
      }

      if (tasks.empty()) {
        continue;
      }

      task = tasks.front();
      tasks.pop();
    }

    try {
      task();
    } catch (const std::exception& ex) {
      Logger::Error("ThreadPool caught exception: {}", ex.what());
      continue;
    }
  }
}
}  // namespace Execution
}  // namespace CppUtils
