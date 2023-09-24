#pragma once
#include "hasher.h"
#include "sha256.h"

namespace CppUtils {
namespace Hashing {
class SHA256Hasher : public Hasher {
 public:
  std::vector<unsigned char> Hash(
      const std::vector<unsigned char>& data) const override;
};
}  // namespace Hashing
}  // namespace CppUtils
