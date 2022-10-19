#include "runtimeexception.h"

RuntimeException::RuntimeException(const std::string& descr)
    : Exception(ExceptionType::Runtime), description(descr) {}

std::string RuntimeException::GetDescription() const noexcept {
  return description;
}
