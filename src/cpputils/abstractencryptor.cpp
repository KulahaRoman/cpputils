#include "abstractencryptor.h"

namespace CppUtils {
namespace Encryption {
AbstractEncryptor::AbstractEncryptor(uint64_t blockSize, uint64_t keySize,
                                     const std::vector<unsigned char>& key)
    : blockSize(blockSize), keySize(keySize), key(key) {
  if (key.size() != keySize) {
    throw std::runtime_error("invalid key length");
  }
}

uint64_t AbstractEncryptor::GetBlockSize() const { return blockSize; }

uint64_t AbstractEncryptor::GetKeySize() const { return keySize; }
}  // namespace Encryption
}  // namespace CppUtils
