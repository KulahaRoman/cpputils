#include "aes256encryptor.h"

namespace CppUtils {
const uint64_t AES256Encryptor::BLOCK_SIZE = 16ull;
const uint64_t AES256Encryptor::KEY_SIZE = 32ull;

AES256Encryptor::AES256Encryptor(const std::vector<unsigned char>& key)
    : AbstractEncryptor(BLOCK_SIZE, KEY_SIZE, key),
      aes(AESKeyLength::AES_256) {}

std::vector<unsigned char> AES256Encryptor::Encrypt(
    const std::vector<unsigned char>& decryptedData) {
  if (decryptedData.size() != BLOCK_SIZE) {
    throw std::runtime_error("Invalid block size.");
  }
  return aes.EncryptECB(decryptedData, key);
}

std::vector<unsigned char> AES256Encryptor::Decrypt(
    const std::vector<unsigned char>& encryptedData) {
  if (encryptedData.size() != BLOCK_SIZE) {
    throw std::runtime_error("Invalid block size.");
  }
  return aes.DecryptECB(encryptedData, key);
}
}  // namespace CppUtils
