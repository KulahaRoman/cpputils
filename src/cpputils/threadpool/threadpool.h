#pragma once
#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

#include "../exceptions/exception.h"
#include "../logger/logger.h"

using Task = std::function<void()>;

constexpr auto MIN_THREADS_NUMBER = 4u;

class ThreadPool {
 public:
  template <class F, class... Args>
  static void AcceptTask(F&& func, Args&&... args) {
    auto& instance = getInstance();

    auto task = std::bind(std::forward<F>(func), std::forward<Args>(args)...);
    auto lock = std::unique_lock<std::mutex>(instance.mx);

    instance.tasks.emplace([task] { task(); });
    instance.cv.notify_one();
  }

 private:
  ThreadPool() : running(true) {
    uint32_t nThreads = std::thread::hardware_concurrency();
    if (nThreads < MIN_THREADS_NUMBER) {
      nThreads = MIN_THREADS_NUMBER;
    }

    for (auto i = 0u; i < nThreads; i++) {
      workers.emplace_back(std::thread(&ThreadPool::threadFunc, this));
    }
  }

  ~ThreadPool() {
    {
      auto lock = std::unique_lock<std::mutex>(mx);
      running = false;
    }

    cv.notify_all();

    for (auto& th : workers) {
      th.join();
    }
  }

  static ThreadPool& getInstance() {
    static ThreadPool threadPool;
    return threadPool;
  }

 private:
  void threadFunc() {
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
      } catch (const Exception& ex) {
#ifndef NDEBUG
        Logger::Error(ex.GetDescription());
#endif
        continue;
      }
    }
  }

 private:
  bool running;
  std::vector<std::thread> workers;
  std::queue<Task> tasks;
  std::mutex mx;
  std::condition_variable cv;
};
