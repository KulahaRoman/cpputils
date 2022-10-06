#include "encryptors.h"

std::unique_ptr<IEncryptor> Encryptors::GetAES256Encryptor(
    const ByteArray& key) {
  return std::make_unique<AES256Encryptor>(key);
}
