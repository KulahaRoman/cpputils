#include "Exception.h"

Exception::Exception(ExceptionType type) : type(type) {}

ExceptionType Exception::GetType() const noexcept { return type; }

#if defined(UNICODE) || defined(_UNICODE)
std::wstring
#else
std::string
#endif
Exception::GetDescription() const noexcept {
  return {};
}