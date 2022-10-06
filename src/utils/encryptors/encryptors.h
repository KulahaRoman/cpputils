#pragma once
#include <memory>

#include "aes256encryptor/aes256encryptor.h"

class Encryptors {
 public:
  static std::unique_ptr<IEncryptor> GetAES256Encryptor(const ByteArray& key);
};
