#pragma once
#include "binaryarchive.h"

namespace CppUtils {
// Represents interface that marks entity so it can be serialized/deserialized.
// Each class which derives 'Serializable' must provide at least default
// constructor, and must override all of virtual methods (destructor is
// optional).
class Serializable {
 public:
  // Serializes class fields of the derived entity.
  virtual void Serialize(BinaryArchive& archive) const = 0;

  // Deserializes class fields of the derived entity.
  virtual void Deserialize(BinaryArchive& archive) = 0;

  // Returns unique ID of derived entity.
  virtual int GetSerialUID() const = 0;

  // Mandatory for deserialization process.
  virtual Serializable& operator=(const Serializable& other) = 0;

  virtual ~Serializable() {}
};
}  // namespace CppUtils
