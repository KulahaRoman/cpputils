#include "encryptors.h"

std::unique_ptr<Encryptor> Encryptors::GetAES256Encryptor(
    const ByteArray& key) {
  return std::make_unique<AES256Encryptor>(key);
}
