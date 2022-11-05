#pragma once
#include "../hasher.h"
#include "md5.h"

class MD5Hasher : public Hasher {
 public:
  std::vector<unsigned char> Hash(
      const std::vector<unsigned char>& data) const override;
};
