#pragma once
#include <stdexcept>
#include <vector>

constexpr uint64_t INITIAL_CAPACITY = 128ull;

class BinaryArchive {
 public:
  // Describes positioning logic.
  // 'BEGIN' - position adjusting relatively to the begin of the internal
  // storage; 'END' - position adjusting relatively to the end of the internal
  // storage; 'RELATIVE' - position adjusting relatively to the current position
  // in the internal storage.
  enum class SeekDirection { BEGIN, END, RELATIVE };

  // Constructs instance and reserves memory for internal storage. By
  // default, storage initial capacity equals 'INITIAL_CAPACITY' constant value.
  BinaryArchive(uint64_t capacity = INITIAL_CAPACITY);

  // Copies 'size' amount of data from the internal storage to the memory
  // location, pointed by 'data' argument. Affects reading position, increasing
  // it by 'size' argument value. Throws exception if 'size' argument value
  // exceeds internal storage bound, considering last reading position.
  void Read(unsigned char* const data, uint64_t size);

  // Copies 'size' amount of data from the memory location, pointed by 'data'
  // argument to internal storage. Affects writing position, increasing it by
  // 'size' argument value.
  // Expands internal storage size while inserting new data.
  // Throws exception if internal storage expanding failed.
  void Write(const unsigned char* const data, uint64_t size);

  // Returns current reading position depending on seek direction.
  uint64_t GetReadPosition(SeekDirection seekDir = SeekDirection::BEGIN) const;

  // Sets new value of reading position depending on seek direction.
  void SetReadPosition(uint64_t pos,
                       SeekDirection seekDir = SeekDirection::BEGIN);

  // Returns current writing position depending on seek direction.
  uint64_t GetWritePosition(SeekDirection seekDir = SeekDirection::BEGIN) const;

  // Sets new value of writing position depending on seek direction.
  void SetWritePosition(uint64_t pos,
                        SeekDirection seekDir = SeekDirection::BEGIN);

  // Sets size of internal storage to 0.
  // Sets reading and writing positions to zero relatively to begin of the
  // storage. Throws exceptions if storage clearing failed.
  void Clear();

  // Returns size of internal storage.
  uint64_t GetSize() const;

  // Returns data pointer to first element of internal storage.
  const unsigned char* GetDataPointer() const;

 private:
  enum class SeekType { READ, WRITE };

  uint64_t calculateNewPosition(uint64_t pos, SeekType seekType,
                                SeekDirection seekDir) const;
  uint64_t calculateCurrentPosition(SeekType seekType,
                                    SeekDirection seekDir) const;

 private:
  // Internal storage.
  std::vector<unsigned char> data;

  // Writing position.
  uint64_t ppos;

  // Reading position.
  uint64_t gpos;
};
