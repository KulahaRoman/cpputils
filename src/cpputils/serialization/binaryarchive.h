#pragma once
#include <stdexcept>
#include <vector>

constexpr uint64_t INITIAL_CAPACITY = 64ull;

class BinaryArchive {
 public:
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

  // Resets reading and writing positions.
  void Reset();

  // Acts same as Reset(), but also sets size of internal storage to 0.
  // Throws exceptions if storage clearing failed.
  void Clear();

  // Returns size of internal storage.
  uint64_t GetSize() const;

  // Returns data pointer to first element of internal storage.
  const unsigned char* GetDataPointer() const;

 private:
  // Internal storage.
  std::vector<unsigned char> data;

  // Writing position.
  uint64_t ppos;

  // Reading position.
  uint64_t gpos;
};
