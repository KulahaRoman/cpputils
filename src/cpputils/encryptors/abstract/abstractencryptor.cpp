#include "abstractencryptor.h"

AbstractEncryptor::AbstractEncryptor(uint64_t blockSize, uint64_t keySize,
                                     ByteArray key)
    : blockSize(blockSize), keySize(keySize), key(key) {
  if (key.size() != keySize) {
    throw RuntimeException("Invalid key length.");
  }
}

uint64_t AbstractEncryptor::GetBlockSize() const { return blockSize; }

uint64_t AbstractEncryptor::GetKeySize() const { return keySize; }
