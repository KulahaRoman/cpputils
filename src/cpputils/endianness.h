#pragma once

namespace CppUtils {
enum class Endianness {
  LITTLE = 0,
  BIG = 1,
};

Endianness GetSystemEndianness() {
  const int value{0x01};
  const void* address{static_cast<const void*>(&value)};
  const unsigned char* leastSignificantAddress{
      static_cast<const unsigned char*>(address)};

  return (*leastSignificantAddress == 0x01) ? Endianness::LITTLE
                                            : Endianness::BIG;
}
}  // namespace CppUtils
