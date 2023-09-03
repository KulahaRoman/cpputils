#pragma once
#include <string>
#include <vector>

class Hasher {
 public:
  virtual std::vector<unsigned char> Hash(
      const std::vector<unsigned char>& data) const = 0;

  virtual ~Hasher() {}
};
