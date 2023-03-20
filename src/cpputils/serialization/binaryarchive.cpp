#include "binaryarchive.h"

BinaryArchive::BinaryArchive(std::size_t capacity) : ppos(-1), gpos(-1) {
  data.reserve(capacity);
}

void BinaryArchive::Read(unsigned char* const data, std::size_t size) {
  try {
    if (size == 0) {
      return;
    }

    if (static_cast<std::size_t>(gpos) + size > this->data.size()) {
      throw std::runtime_error("Reading position out of bound.");
    }

    auto beginPosition = this->data.begin() + gpos;
    auto endPosition = beginPosition + static_cast<int32_t>(size);

    std::copy(beginPosition, endPosition, data);

    gpos += static_cast<int32_t>(size);
  } catch (...) {
    throw std::runtime_error("Failed to read data from internal storage.");
  }
}

void BinaryArchive::Write(const unsigned char* const data, std::size_t size) {
  try {
    if (size == 0) {
      return;
    }

    this->data.insert(this->data.begin() + ppos, data,
                      data + static_cast<int32_t>(size));

    ppos += static_cast<int32_t>(size);
  } catch (...) {
    throw std::runtime_error("Failed to write data to internal storage.");
  }
}

int32_t BinaryArchive::GetReadPosition(SeekDirection seekDir) const {
  return calculateCurrentPosition(SeekType::READ, seekDir);
}

void BinaryArchive::SetReadPosition(int32_t pos, SeekDirection seekDir) {
  auto storageSize = data.size();

  if (storageSize == 0) {
    throw std::runtime_error(
        "Failed to set new reading position: storage is empty.");
  }

  auto newPosition = static_cast<std::size_t>(
      calculateNewPosition(pos, SeekType::READ, seekDir));

  if (newPosition < 0 || newPosition >= storageSize) {
    throw std::runtime_error(
        "Failed to set new reading position: out of bounds.");
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
        "Failed to set new writing position: storage is empty.");
  }

  auto newPosition = static_cast<std::size_t>(
      calculateNewPosition(pos, SeekType::WRITE, seekDir));

  if (newPosition < 0 || newPosition >= storageSize) {
    throw std::runtime_error(
        "Failed to set new writing position: out of bounds.");
  }

  ppos = static_cast<int32_t>(newPosition);
}

void BinaryArchive::Clear() {
  try {
    data.clear();
  } catch (...) {
    throw std::runtime_error("Failed to clear internal storage.");
  }

  gpos = -1;
  ppos = -1;
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
      calculatedPosition = static_cast<int>(storageSize - 1 - pos);
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

  if (storageSize == 0) {
    return currentPosition;
  }

  auto calculatedPosition = 0;

  switch (seekDir) {
    case SeekDirection::BEGIN: {
      calculatedPosition = currentPosition;
      break;
    }
    case SeekDirection::END: {
      calculatedPosition = static_cast<int>(storageSize - 1 - currentPosition);
      break;
    }
    case SeekDirection::RELATIVE: {
      calculatedPosition = 0;
      break;
    }
  }

  return calculatedPosition;
}
