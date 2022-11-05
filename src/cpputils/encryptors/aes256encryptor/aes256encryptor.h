#pragma once
#include <vector>

#include "../abstract/abstractencryptor.h"
#include "aes.h"

constexpr uint64_t BLOCK_SIZE = 16ull;
constexpr uint64_t KEY_SIZE = 32ull;

class AES256Encryptor : public AbstractEncryptor {
 public:
  AES256Encryptor(const std::vector<unsigned char>& key);

  std::vector<unsigned char> Encrypt(
      const std::vector<unsigned char>& decryptedData) override;
  std::vector<unsigned char> Decrypt(
      const std::vector<unsigned char>& encryptedData) override;

 private:
  AES aes;
};
