#pragma once
#include <stdexcept>
#include <vector>

namespace CppUtils {
namespace Serialization {
class BinaryArchive {
 public:
#ifdef BEGIN
#undef BEGIN
#endif

#ifdef END
#undef END
#endif

#ifdef RELATIVE
#undef RELATIVE
#endif

  // Describes positioning logic.
  // 'BEGIN' - position adjusting relatively to the begin of the internal
  // storage; 'END' - position adjusting relatively to the end of the internal
  // storage; 'RELATIVE' - position adjusting relatively to the current position
  // in the internal storage.
  enum class SeekDirection { BEGIN, END, RELATIVE };

  // Constructs instance and reserves memory for internal storage. By
  // default, storage initial capacity equals 'INITIAL_CAPACITY' constant value.
  BinaryArchive(std::size_t capacity = INITIAL_CAPACITY);

  // Copies 'size' amount of data from the internal storage to the memory
  // location, pointed by 'data' argument. Affects reading position, increasing
  // it by 'size' argument value. Throws exception if 'size' argument value
  // exceeds internal storage bound, considering last reading position.
  void Read(unsigned char* const data, std::size_t size);

  // Copies 'size' amount of data from the memory location, pointed by 'data'
  // argument to internal storage. Affects writing position, increasing it by
  // 'size' argument value.
  // Expands internal storage size while inserting new data.
  // Throws exception if internal storage expanding failed.
  void Write(const unsigned char* const data, std::size_t size);

  // Returns current reading position depending on seek direction.
  int32_t GetReadPosition(SeekDirection seekDir = SeekDirection::BEGIN) const;

  // Sets new value of reading position depending on seek direction.
  void SetReadPosition(int32_t pos,
                       SeekDirection seekDir = SeekDirection::BEGIN);

  // Returns current writing position depending on seek direction.
  int32_t GetWritePosition(SeekDirection seekDir = SeekDirection::BEGIN) const;

  // Sets new value of writing position depending on seek direction.
  void SetWritePosition(int32_t pos,
                        SeekDirection seekDir = SeekDirection::BEGIN);

  // Sets size of internal storage to 0.
  // Sets reading and writing positions to zero relatively to begin of the
  // storage. Throws exceptions if storage clearing failed.
  void Clear();

  // Returns size of internal storage.
  std::size_t GetSize() const;

  // Returns data pointer to first element of internal storage.
  const unsigned char* GetDataPointer() const;

 private:
  enum class SeekType { READ, WRITE };

  int32_t calculateNewPosition(int32_t pos, SeekType seekType,
                               SeekDirection seekDir) const;
  int32_t calculateCurrentPosition(SeekType seekType,
                                   SeekDirection seekDir) const;

 private:
  // Private const definitions.
  static const std::size_t INITIAL_CAPACITY;
  static const int32_t UNDEFINED_POSITION;

  // Internal storage.
  std::vector<unsigned char> data;

  // Writing position.
  int32_t ppos;

  // Reading position.
  int32_t gpos;
};
}  // namespace Serialization
}  // namespace CppUtils
