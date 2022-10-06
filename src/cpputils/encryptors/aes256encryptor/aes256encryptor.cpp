#include "aes256encryptor.h"

AES256Encryptor::AES256Encryptor(const ByteArray& key)
    : AbstractEncryptor(BLOCK_SIZE, KEY_SIZE, key),
      aes(AESKeyLength::AES_256) {}

ByteArray AES256Encryptor::Encrypt(const ByteArray& decryptedData) {
  return aes.EncryptECB(decryptedData, key);
}

ByteArray AES256Encryptor::Decrypt(const ByteArray& encryptedData) {
  return aes.DecryptECB(encryptedData, key);
}
