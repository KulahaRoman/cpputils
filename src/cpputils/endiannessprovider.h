#pragma once

namespace CppUtils {
namespace Serialization {
class EndiannessProvider {
 public:
  enum class Endianness {
    LITTLE = 0,
    BIG = 1,
  };

  static Endianness GetSystemEndianness();
};
}  // namespace Serialization
}  // namespace CppUtils
