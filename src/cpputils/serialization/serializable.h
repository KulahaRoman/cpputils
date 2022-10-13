#pragma once
#include <functional>
#include <memory>

class InputStream;
class OutputStream;

class Serializable {
 public:
  virtual void Serialize(const std::shared_ptr<OutputStream> &stream) const = 0;
  virtual void Serialize(
      const std::shared_ptr<OutputStream> &stream,
      const std::function<void(uint64_t)> &callback) const = 0;

  virtual ~Serializable() {}
};