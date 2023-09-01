#pragma once
#include "binaryarchive.h"

class Serializable {
 public:
  virtual void Serialize(BinaryArchive& archive) const = 0;
  virtual void Deserialize(BinaryArchive& archive) = 0;

  virtual ~Serializable() {}
};
