#include "synchronizers.h"

std::unique_ptr<CountDownLatch> Synchronizers::GetCountDownLatch(
    uint64_t size) {
  return std::make_unique<CountDownLatch>(size);
}
