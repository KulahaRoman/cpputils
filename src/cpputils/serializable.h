#pragma once
#include "binaryarchive.h"

namespace CppUtils {
namespace Serialization {
// Represents interface that marks entity so it can be serialized/deserialized.
// Each class which derives 'Serializable' must provide a default
// constructor, and must override all of pure virtual methods.

class Serializable {
 public:
  virtual void Serialize(BinaryArchive& archive) const = 0;
  virtual void Deserialize(BinaryArchive& archive) = 0;

  virtual ~Serializable() = default;
};
}  // namespace Serialization
}  // namespace CppUtils
