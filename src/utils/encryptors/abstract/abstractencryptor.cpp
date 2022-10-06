#include "abstractencryptor.h"

AbstractEncryptor::AbstractEncryptor(uint64_t blockSize, uint64_t keySize,
                                     ByteArray key)
    : blockSize(blockSize), keySize(keySize), key(key) {
  if (key.size() != keySize) {
    throw RuntimeException(
#if defined(UNICODE) || defined(_UNICODE)
        L"Invalid key length."
#else
        "Invalid key length."
#endif
    );
  }
}

uint64_t AbstractEncryptor::GetBlockSize() const { return blockSize; }

uint64_t AbstractEncryptor::GetKeySize() const { return keySize; }
