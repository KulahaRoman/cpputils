#pragma once
#include <cstdint>
#include <vector>

namespace CppUtils {
namespace Encryption {
class Encryptor {
 public:
  virtual std::vector<unsigned char> Encrypt(
      const std::vector<unsigned char>&) = 0;
  virtual std::vector<unsigned char> Decrypt(
      const std::vector<unsigned char>&) = 0;
  virtual uint64_t GetBlockSize() const = 0;
  virtual uint64_t GetKeySize() const = 0;

  virtual ~Encryptor() {}
};
}  // namespace Encryption
}  // namespace CppUtils
