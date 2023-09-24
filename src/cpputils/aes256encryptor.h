#pragma once
#include <vector>

#include "abstractencryptor.h"
#include "aes.h"

namespace CppUtils {
namespace Encryption {
class AES256Encryptor : public AbstractEncryptor {
 public:
  AES256Encryptor(const std::vector<unsigned char>& key);

  std::vector<unsigned char> Encrypt(
      const std::vector<unsigned char>& decryptedData) override;
  std::vector<unsigned char> Decrypt(
      const std::vector<unsigned char>& encryptedData) override;

 private:
  static const uint64_t BLOCK_SIZE;
  static const uint64_t KEY_SIZE;

  AES aes;
};
}  // namespace Encryption
}  // namespace CppUtils
