#pragma once
#include <vector>

#include "../abstract/abstractencryptor.h"
#include "aes.h"

constexpr uint64_t BLOCK_SIZE = 16ull;
constexpr uint64_t KEY_SIZE = 32ull;

class AES256Encryptor : public AbstractEncryptor {
 public:
  AES256Encryptor(const ByteArray& key);

  ByteArray Encrypt(const ByteArray& decryptedData) override;
  ByteArray Decrypt(const ByteArray& encryptedData) override;

 private:
  AES aes;
};
