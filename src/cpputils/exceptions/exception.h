#pragma once
#include <string>

#include "exceptiontype.h"

class Exception {
 public:
  Exception(ExceptionType type);

  ExceptionType GetType() const noexcept;
  virtual std::string GetDescription() const noexcept;

  virtual ~Exception() {}

 private:
  ExceptionType type;
};
