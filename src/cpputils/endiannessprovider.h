#pragma once

namespace CppUtils {
class EndiannessProvider {
 public:
  enum class Endianness {
    LITTLE = 0,
    BIG = 1,
  };

  static Endianness GetSystemEndianness();
};
}  // namespace CppUtils
