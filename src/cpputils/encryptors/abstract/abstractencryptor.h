#pragma once
#include "../../exceptions/exceptions.h"
#include "../encryptor.h"

class AbstractEncryptor : public Encryptor {
 public:
  AbstractEncryptor(uint64_t blockSize, uint64_t keySize, ByteArray key);

  uint64_t GetBlockSize() const override;
  uint64_t GetKeySize() const override;

 protected:
  const ByteArray key;

 private:
  const uint64_t blockSize;
  const uint64_t keySize;
};
