#pragma once
#include <stdexcept>

#include "../encryptor.h"

class AbstractEncryptor : public Encryptor {
 public:
  AbstractEncryptor(uint64_t blockSize, uint64_t keySize,
                    const std::vector<unsigned char>& key);

  uint64_t GetBlockSize() const override;
  uint64_t GetKeySize() const override;

 protected:
  const std::vector<unsigned char> key;

 private:
  const uint64_t blockSize;
  const uint64_t keySize;
};
