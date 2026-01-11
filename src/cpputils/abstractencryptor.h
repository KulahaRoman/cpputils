#pragma once
#include <stdexcept>

#include "encryptor.h"

namespace CppUtils {
namespace Encryption {
class AbstractEncryptor : public Encryptor {
 public:
  AbstractEncryptor(std::size_t blockSize, std::size_t keySize,
                    const std::vector<unsigned char>& key);

  std::size_t GetBlockSize() const override;
  std::size_t GetKeySize() const override;

 protected:
  const std::vector<unsigned char> key;

 private:
  const std::size_t blockSize;
  const std::size_t keySize;
};
}  // namespace Encryption
}  // namespace CppUtils
