#include "encryptors.h"

std::shared_ptr<Encryptor> Encryptors::GetAES256Encryptor(
    const ByteArray& key) {
  return std::make_shared<AES256Encryptor>(key);
}
