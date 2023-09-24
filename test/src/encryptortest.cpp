#include <cpputils/aes256encryptor.h>
#include <gtest/gtest.h>

using namespace CppUtils::Encryption;

TEST(EncryptorTest, AES256) {
  std::vector<unsigned char> key(32, 'A');
  std::vector<unsigned char> blockToEncrypt(16, 'B');

  auto encryptor = std::make_unique<AES256Encryptor>(key);

  auto encryptedBlock = encryptor->Encrypt(blockToEncrypt);

  unsigned char preEncryptedBytes[17] =
      "\xcf\xe9\x60\xb2\x63\x73\x52\x53\xdf\x64\xe7\x6a\x51\xef\x42\x88";
  std::vector<unsigned char> preEncryptedBlock{
      reinterpret_cast<unsigned char*>(&preEncryptedBytes),
      reinterpret_cast<unsigned char*>(&preEncryptedBytes) + 16};

  ASSERT_TRUE(encryptedBlock == preEncryptedBlock);

  auto decryptedBlock = encryptor->Decrypt(encryptedBlock);

  ASSERT_TRUE(decryptedBlock == blockToEncrypt);
}
