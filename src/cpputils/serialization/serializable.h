#pragma once
#include <functional>
#include <memory>
#include <span>

class Serializable {
 public:
  virtual uint64_t Serialize(std::vector<unsigned char>& binary) const = 0;
  virtual uint64_t Deserialize(const std::span<unsigned char>& binary) = 0;

  virtual ~Serializable() {}
};
