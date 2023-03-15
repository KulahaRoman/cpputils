#include "binaryarchive.h"

BinaryArchive::BinaryArchive(uint64_t capacity) : ppos(0ull), gpos(0ull) {
  data.reserve(capacity);
}

void BinaryArchive::Read(unsigned char* const data, uint64_t size) {
  try {
    if (gpos + size >= this->data.size()) {
      throw std::runtime_error("Reading position out of bound.");
    }

    auto beginPosition = this->data.end() + gpos;
    auto endPosition = beginPosition + size;

    std::copy(beginPosition, endPosition, data);

    gpos += size;
  } catch (...) {
    throw std::runtime_error("Failed to read data from internal storage.");
  }
}

void BinaryArchive::Write(const unsigned char* const data, uint64_t size) {
  try {
    this->data.insert(this->data.end() + ppos, data, data + size);

    ppos += size;
  } catch (...) {
    throw std::runtime_error("Failed to expand internal storage.");
  }
}

void BinaryArchive::Reset() {
  ppos = 0ull;
  gpos = 0ull;
}

void BinaryArchive::Clear() {
  try {
    data.clear();
  } catch (...) {
    throw std::runtime_error("Failed to clear internal storage.");
  }

  Reset();
}

uint64_t BinaryArchive::GetSize() const {
  return static_cast<uint64_t>(data.size());
}

const unsigned char* BinaryArchive::GetDataPointer() const {
  return data.data();
}
