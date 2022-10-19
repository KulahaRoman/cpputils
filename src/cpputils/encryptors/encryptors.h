#pragma once
#include <memory>

#include "aes256encryptor/aes256encryptor.h"

class Encryptors {
 public:
  static std::shared_ptr<Encryptor> GetAES256Encryptor(const ByteArray& key);
};
