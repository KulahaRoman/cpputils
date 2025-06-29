#include "binaryarchive.h"

namespace CppUtils {
namespace Serialization {
const std::size_t BinaryArchive::INITIAL_CAPACITY = 1024ull;
const int32_t BinaryArchive::UNDEFINED_POSITION = -1;

BinaryArchive::BinaryArchive(std::size_t capacity) : ppos(0), gpos(0) {
  data.reserve(capacity);
}

void BinaryArchive::Read(unsigned char* const data, std::size_t size) {
  try {
    if (size == 0) {
      return;
    }

    if (static_cast<std::size_t>(gpos) + size > this->data.size()) {
      throw std::runtime_error("reading position out of bound");
    }

    auto beginPosition = this->data.begin() + gpos;
    auto endPosition = beginPosition + static_cast<int32_t>(size);

    std::copy(beginPosition, endPosition, data);

    gpos += static_cast<int32_t>(size);
  } catch (...) {
    throw std::runtime_error("failed to read data from internal storage");
  }
}

void BinaryArchive::Write(const unsigned char* const data, std::size_t size) {
  try {
    if (size == 0) {
      return;
    }

    auto newSize = ppos + size;
    if (newSize > this->data.size()) {
      this->data.resize(newSize);
    }

    std::copy(data, data + static_cast<int32_t>(size),
              this->data.data() + ppos);

    ppos += static_cast<int32_t>(size);
  } catch (...) {
    throw std::runtime_error("failed to write data to internal storage");
  }
}

int32_t BinaryArchive::GetReadPosition(SeekDirection seekDir) const {
  return calculateCurrentPosition(SeekType::READ, seekDir);
}

void BinaryArchive::SetReadPosition(int32_t pos, SeekDirection seekDir) {
  auto storageSize = data.size();

  if (storageSize == 0) {
    throw std::runtime_error(
        "failed to set new reading position: storage is empty");
  }

  auto newPosition = static_cast<std::size_t>(
      calculateNewPosition(pos, SeekType::READ, seekDir));

  if (newPosition < 0 || newPosition >= storageSize) {
    throw std::runtime_error(
        "failed to set new reading position: out of bounds");
  }

  gpos = static_cast<int32_t>(newPosition);
}

int32_t BinaryArchive::GetWritePosition(SeekDirection seekDir) const {
  return calculateCurrentPosition(SeekType::WRITE, seekDir);
}

void BinaryArchive::SetWritePosition(int32_t pos, SeekDirection seekDir) {
  auto storageSize = data.size();

  if (storageSize == 0) {
    throw std::runtime_error(
        "failed to set new writing position: storage is empty");
  }

  auto newPosition = static_cast<std::size_t>(
      calculateNewPosition(pos, SeekType::WRITE, seekDir));

  if (newPosition < 0 || newPosition > storageSize) {
    throw std::runtime_error(
        "failed to set new writing position: out of bounds");
  }

  ppos = static_cast<int32_t>(newPosition);
}

void BinaryArchive::Clear() {
  try {
    data.clear();
  } catch (...) {
    throw std::runtime_error("failed to clear internal storage");
  }

  gpos = 0;
  ppos = 0;
}

std::size_t BinaryArchive::GetSize() const { return data.size(); }

const unsigned char* BinaryArchive::GetDataPointer() const {
  return data.data();
}

int32_t BinaryArchive::calculateNewPosition(int32_t pos, SeekType seekType,
                                            SeekDirection seekDir) const {
  auto storageSize = data.size();
  auto currentPosition = (seekType == SeekType::READ ? gpos : ppos);
  auto calculatedPosition = 0;

  switch (seekDir) {
    case SeekDirection::BEGIN: {
      calculatedPosition = pos;
      break;
    }
    case SeekDirection::END: {
      calculatedPosition = static_cast<int>(storageSize - pos);
      break;
    }
    case SeekDirection::RELATIVE: {
      calculatedPosition = currentPosition + pos;
      break;
    }
  }

  return calculatedPosition;
}

int32_t BinaryArchive::calculateCurrentPosition(SeekType seekType,
                                                SeekDirection seekDir) const {
  auto storageSize = data.size();

  auto currentPosition = (seekType == SeekType::READ ? gpos : ppos);
  auto calculatedPosition = 0;

  switch (seekDir) {
    case SeekDirection::BEGIN: {
      calculatedPosition = currentPosition;
      break;
    }
    case SeekDirection::END: {
      calculatedPosition = static_cast<int>(storageSize - currentPosition);
      break;
    }
    case SeekDirection::RELATIVE: {
      calculatedPosition = 0;
      break;
    }
  }

  return calculatedPosition;
}
}  // namespace Serialization
}  // namespace CppUtils
