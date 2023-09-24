#pragma once
#include "hasher.h"
#include "md5.h"

namespace CppUtils {
namespace Hashing {
class MD5Hasher : public Hasher {
 public:
  std::vector<unsigned char> Hash(
      const std::vector<unsigned char>& data) const override;
};
}  // namespace Hashing
}  // namespace CppUtils
