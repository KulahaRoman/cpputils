#pragma once
#include <cstddef>
#include <functional>
#include <memory>

class Serializable {
 public:
  virtual uint64_t Serialize(std::vector<std::byte>& binary) const = 0;
  virtual uint64_t Deserialize(const std::span<std::byte>& binary) = 0;

  virtual ~Serializable() {}
};
