#pragma once
#include <string>
#include <vector>

namespace CppUtils {
namespace Hashing {
class Hasher {
 public:
  virtual std::vector<unsigned char> Hash(
      const std::vector<unsigned char>& data) const = 0;

  virtual ~Hasher() {}
};
}  // namespace Hashing
}  // namespace CppUtils
