#include "countdownlatch.h"

CountDownLatch::CountDownLatch(uint64_t size) : size(size), completed(0ull) {}

void CountDownLatch::Await() {
  auto predicate = [this] { return size == completed; };
  auto lock = std::unique_lock<std::mutex>(mx);

  cv.wait(lock, predicate);
}

void CountDownLatch::CountDown() {
  auto lock = std::unique_lock<std::mutex>(mx);
  completed++;
  cv.notify_one();
}

void CountDownLatch::Reset() {
  auto lock = std::unique_lock<std::mutex>(mx);
  completed = 0;
}
