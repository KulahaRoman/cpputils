#include "runtimeexception.h"

RuntimeException::RuntimeException(const
#if defined(UNICODE) || defined(_UNICODE)
                                   std::wstring
#else
                                   std::string
#endif
                                       & descr)
    : Exception(ExceptionType::Runtime), description(descr) {
}

#if defined(UNICODE) || defined(_UNICODE)
std::wstring
#else
std::string
#endif
RuntimeException::GetDescription() const noexcept {
  return description;
}
