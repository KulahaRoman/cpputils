#include "endiannessprovider.h"

namespace CppUtils {
namespace Serialization {
EndiannessProvider::Endianness EndiannessProvider::GetSystemEndianness() {
  const int value{0x01};
  const void* address{static_cast<const void*>(&value)};
  const unsigned char* leastSignificantAddress{
      static_cast<const unsigned char*>(address)};

  return (*leastSignificantAddress == 0x01) ? Endianness::LITTLE
                                            : Endianness::BIG;
}
}  // namespace Serialization
}  // namespace CppUtils
