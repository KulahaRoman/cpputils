#pragma once
#include <string>

#include "exceptiontype.h"

class Exception {
 public:
  Exception(ExceptionType type);

  ExceptionType GetType() const noexcept;
  virtual
#if defined(UNICODE) || defined(_UNICODE)
      std::wstring
#else
      std::string
#endif
      GetDescription() const noexcept;

  virtual ~Exception() {}

 private:
  ExceptionType type;
};
