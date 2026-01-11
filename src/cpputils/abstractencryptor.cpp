#include "abstractencryptor.h"

namespace CppUtils {
namespace Encryption {
AbstractEncryptor::AbstractEncryptor(std::size_t blockSize, std::size_t keySize,
                                     const std::vector<unsigned char>& key)
    : blockSize(blockSize), keySize(keySize), key(key) {
  if (key.size() != keySize) {
    throw std::runtime_error("invalid key length");
  }
}

std::size_t AbstractEncryptor::GetBlockSize() const { return blockSize; }

std::size_t AbstractEncryptor::GetKeySize() const { return keySize; }
}  // namespace Encryption
}  // namespace CppUtils
