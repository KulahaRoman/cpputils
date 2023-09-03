#pragma once
#include <condition_variable>
#include <cstdint>
#include <mutex>

namespace CppUtils {
class CountDownLatch {
 public:
  CountDownLatch(uint64_t size);

  void Await();
  void CountDown();
  void Reset();

 private:
  uint64_t size;
  uint64_t completed;

  std::mutex mx;
  std::condition_variable cv;
};
}  // namespace CppUtils
