#include "md5hasher.h"

namespace CppUtils {
namespace Hashing {
std::vector<unsigned char> MD5Hasher::Hash(
    const std::vector<unsigned char>& data) const {
  MD5 md5;
  return md5.result(data);
}
}  // namespace Hashing
}  // namespace CppUtils
