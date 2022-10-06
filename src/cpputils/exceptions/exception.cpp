#include "Exception.h"

Exception::Exception(ExceptionType type) : type(type) {}

ExceptionType Exception::GetType() const noexcept { return type; }
