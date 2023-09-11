#pragma once
#include "binaryarchive.h"

namespace CppUtils {
// Represents interface that marks entity so it can be serialized/deserialized.
// Each class which derives 'Serializable' must provide at least default
// constructor, and must override all of pure virtual methods.
// Here is used CRTP for virtual copy assignment operator to specify complete
// type instead of 'const Serializable&' which should be staticaly casted to
// complete type by user in every derived class to access some derived class
// fields.

template <class Derived>
class Serializable {
 public:
  // Serializes class fields of the derived entity.
  virtual void Serialize(BinaryArchive& archive) const = 0;

  // Deserializes class fields of the derived entity.
  virtual void Deserialize(BinaryArchive& archive) = 0;

  // Returns unique ID of derived entity.
  virtual int GetSerialUID() const = 0;

  // Mandatory for deserialization process.
  virtual Derived& operator=(const Derived& other) = 0;

  virtual ~Serializable() {}
};
}  // namespace CppUtils
