#pragma once
#include <functional>
#include <memory>

class IInputStream;
class IOutputStream;
class IAsyncInputStream;
class IAsyncOutputStream;

class ISerializable {
 public:
  virtual void Serialize(
      const std::shared_ptr<IOutputStream> &stream) const = 0;
  virtual void Serialize(
      const std::shared_ptr<IAsyncOutputStream> &stream,
      const std::function<void(uint64_t)> &callback) const = 0;

  virtual ~ISerializable() {}
};