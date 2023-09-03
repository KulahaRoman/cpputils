#include "aes256encryptor.h"

namespace CppUtils {
AES256Encryptor::AES256Encryptor(const std::vector<unsigned char>& key)
    : AbstractEncryptor(BLOCK_SIZE, KEY_SIZE, key),
      aes(AESKeyLength::AES_256) {}

std::vector<unsigned char> AES256Encryptor::Encrypt(
    const std::vector<unsigned char>& decryptedData) {
  return aes.EncryptECB(decryptedData, key);
}

std::vector<unsigned char> AES256Encryptor::Decrypt(
    const std::vector<unsigned char>& encryptedData) {
  return aes.DecryptECB(encryptedData, key);
}
}  // namespace CppUtils
