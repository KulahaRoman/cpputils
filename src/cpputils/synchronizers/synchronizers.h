#pragma once
#include <memory>

#include "countdownlatch/countdownlatch.h"

class Synchronizers {
 public:
  static std::shared_ptr<CountDownLatch> GetCountDownLatch(uint64_t size);
};
