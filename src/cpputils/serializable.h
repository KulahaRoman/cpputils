#pragma once
#include <memory>
#include <set>

#include "binaryarchive.h"

namespace CppUtils {
namespace Serialization {
// Represents interface that marks entity so it can be serialized/deserialized.
// Each class which derives 'Serializable' must provide at least default
// constructor, and must override all of pure virtual methods.

class Serializable {
 public:
  virtual void Serialize(BinaryArchive& archive) const = 0;
  virtual void Deserialize(BinaryArchive& archive) = 0;

  virtual ~Serializable() { cachedSharedObjects.clear(); };

 protected:
  template <class T>
  void cacheSharedObject(const std::weak_ptr<T>& object);

 private:
  std::set<std::shared_ptr<void>> cachedSharedObjects;
};

template <class T>
void Serializable::cacheSharedObject(const std::weak_ptr<T>& object) {
  auto erasedSharedPointer = std::static_pointer_cast<void>(object.lock());
  cachedSharedObjects.emplace(erasedSharedPointer);
}
}  // namespace Serialization
}  // namespace CppUtils
