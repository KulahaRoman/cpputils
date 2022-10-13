#pragma once
#include <cstdint>
#include <vector>

using ByteArray = std::vector<unsigned char>;

class Encryptor {
 public:
  virtual ByteArray Encrypt(const ByteArray&) = 0;
  virtual ByteArray Decrypt(const ByteArray&) = 0;
  virtual uint64_t GetBlockSize() const = 0;
  virtual uint64_t GetKeySize() const = 0;

  virtual ~Encryptor() {}
};
