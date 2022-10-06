#pragma once
#include "../exception.h"

class RuntimeException : public Exception {
 public:
  RuntimeException(const
#if defined(UNICODE) || defined(_UNICODE)
                   std::wstring
#else
                   std::string
#endif
                       & descr);

#if defined(UNICODE) || defined(_UNICODE)
  std::wstring
#else
  std::string
#endif
  GetDescription() const noexcept override;

 private:
#if defined(UNICODE) || defined(_UNICODE)
  std::wstring description;
#else
  std::string description;
#endif
};
