#pragma once
#include "../exception.h"

class RuntimeException : public Exception {
 public:
  RuntimeException(const std::string& descr);

  std::string GetDescription() const noexcept override;

 private:
  std::string description;
};
