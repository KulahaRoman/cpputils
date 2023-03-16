#include "binaryarchive.h"

BinaryArchive::BinaryArchive(uint64_t capacity) : ppos(0ull), gpos(0ull) {
  data.reserve(capacity);
}

void BinaryArchive::Read(unsigned char* const data, uint64_t size) {
  try {
    if (gpos + size > this->data.size()) {
      throw std::runtime_error("Reading position out of bound.");
    }

    auto beginPosition = this->data.begin() + gpos;
    auto endPosition = beginPosition + size;

    std::copy(beginPosition, endPosition, data);

    gpos += size;
  } catch (...) {
    throw std::runtime_error("Failed to read data from internal storage.");
  }
}

void BinaryArchive::Write(const unsigned char* const data, uint64_t size) {
  try {
    this->data.insert(this->data.begin() + ppos, data, data + size);

    ppos += size;
  } catch (...) {
    throw std::runtime_error("Failed to expand internal storage.");
  }
}

uint64_t BinaryArchive::GetReadPosition(SeekDirection seekDir) const {
  return calculateCurrentPosition(SeekType::READ, seekDir);
}

void BinaryArchive::SetReadPosition(uint64_t pos, SeekDirection seekDir) {
  auto storageSize = static_cast<uint64_t>(data.size());
  auto newPosition = calculateNewPosition(pos, SeekType::READ, seekDir);

  if (newPosition >= storageSize) {
    throw std::runtime_error("BinaryArchive position out of bounds.");
  }

  gpos = newPosition;
}

uint64_t BinaryArchive::GetWritePosition(SeekDirection seekDir) const {
  return calculateCurrentPosition(SeekType::WRITE, seekDir);
}

void BinaryArchive::SetWritePosition(uint64_t pos, SeekDirection seekDir) {
  auto storageSize = static_cast<uint64_t>(data.size());
  auto newPosition = calculateNewPosition(pos, SeekType::WRITE, seekDir);

  if (newPosition >= storageSize) {
    throw std::runtime_error("BinaryArchive position out of bounds.");
  }

  ppos = newPosition;
}

void BinaryArchive::Clear() {
  try {
    data.clear();
  } catch (...) {
    throw std::runtime_error("Failed to clear internal storage.");
  }

  gpos = 0ull;
  ppos = 0ull;
}

uint64_t BinaryArchive::GetSize() const {
  return static_cast<uint64_t>(data.size());
}

const unsigned char* BinaryArchive::GetDataPointer() const {
  return data.data();
}

uint64_t BinaryArchive::calculateNewPosition(uint64_t pos, SeekType seekType,
                                             SeekDirection seekDir) const {
  auto storageSize = static_cast<uint64_t>(data.size());
  auto currentPosition = (seekType == SeekType::READ ? gpos : ppos);
  auto calculatedPosition = 0ull;

  switch (seekDir) {
    case SeekDirection::BEGIN: {
      calculatedPosition = pos;
      break;
    }
    case SeekDirection::END: {
      calculatedPosition = storageSize - 1 - pos;
      break;
    }
    case SeekDirection::RELATIVE: {
      calculatedPosition = currentPosition + pos;
      break;
    }
  }

  return calculatedPosition;
}

uint64_t BinaryArchive::calculateCurrentPosition(SeekType seekType,
                                                 SeekDirection seekDir) const {
  auto storageSize = static_cast<uint64_t>(data.size());
  auto currentPosition = (seekType == SeekType::READ ? gpos : ppos);
  auto calculatedPosition = 0ull;

  switch (seekDir) {
    case SeekDirection::BEGIN: {
      calculatedPosition = currentPosition;
    }
    case SeekDirection::END: {
      calculatedPosition = storageSize - 1 - currentPosition;
    }
    case SeekDirection::RELATIVE: {
      calculatedPosition = 0ull;
    }
  }

  return calculatedPosition;
}
