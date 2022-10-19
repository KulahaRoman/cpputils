#include "synchronizers.h"

std::shared_ptr<CountDownLatch> Synchronizers::GetCountDownLatch(
    uint64_t size) {
  return std::make_shared<CountDownLatch>(size);
}
