#pragma once
#include <algorithm>
#include <deque>
#include <forward_list>
#include <list>
#include <map>
#include <memory>
#include <queue>
#include <set>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "binaryarchive.h"
#include "endiannessprovider.h"
#include "serializable.h"

namespace CppUtils {
// Represents a singletone class that does mostly all job of serialization.
// Currently supports integral types, enum types, STL strings, several
// containers and custom Serializable class. Detects and prevents cyclic
// references. Checks system endianness in runtime so it's fine
// to use this serializer to exchange some data between Linux and Windows apps.

#define CYCLIC_WEAK_REFERENCE(field) \
  if (field.lock()->field.lock()) {  \
    cacheSharedObject(field);        \
  }

class Serializer {
 public:
  template <class T>
  static void Serialize(
      const T value, BinaryArchive& archive,
      std::enable_if_t<std::is_integral<T>::value, T>* = nullptr) {
    try {
      // let's assume that network endian is big
      T temp = 0;

      if (EndiannessProvider::GetSystemEndianness() ==
          EndiannessProvider::Endianness::LITTLE) {
        temp = swapBytes(value);
      } else {
        temp = value;
      }

      archive.Write(reinterpret_cast<const unsigned char*>(&temp),
                    sizeof(temp));
    } catch (...) {
      throw std::runtime_error("Failed to serialize integral type value.");
    }
  }

  template <class T>
  static void Serialize(
      const T value, BinaryArchive& archive,
      std::enable_if_t<std::is_enum<T>::value, T>* = nullptr) {
    try {
      Serialize(static_cast<std::underlying_type_t<T>>(value), archive);
    } catch (...) {
      throw std::runtime_error("Failed to serialize enum type value.");
    }
  }

  static void Serialize(const std::string& str, BinaryArchive& archive) {
    try {
      auto strSizeInBytes = static_cast<uint64_t>(str.size());

      Serialize(strSizeInBytes, archive);

      archive.Write(reinterpret_cast<const unsigned char*>(str.data()),
                    static_cast<std::size_t>(strSizeInBytes));
    } catch (...) {
      throw std::runtime_error("Failed to serialize std::string.");
    }
  }

  static void Serialize(const std::wstring& wstr, BinaryArchive& archive) {
    try {
      auto strSizeInBytes =
          static_cast<uint64_t>(wstr.size() * sizeof(wchar_t));

      Serialize(strSizeInBytes, archive);

      archive.Write(reinterpret_cast<const unsigned char*>(wstr.data()),
                    static_cast<std::size_t>(strSizeInBytes));
    } catch (...) {
      throw std::runtime_error("Failed to serialize std::wstring.");
    }
  }

  template <class T1, class T2>
  static void Serialize(const std::pair<T1, T2>& pair, BinaryArchive& archive) {
    try {
      Serialize(pair.first, archive);
      Serialize(pair.second, archive);
    } catch (...) {
      throw std::runtime_error("Failed to serialize std::pair<T1,T2>.");
    }
  }

  template <class T, std::size_t N>
  static void Serialize(const std::array<T, N>& array, BinaryArchive& archive) {
    try {
      for (const auto& value : array) {
        Serialize(value, archive);
      }
    } catch (...) {
      throw std::runtime_error("Failed to serialize std::array<T,N>.");
    }
  }

  template <class K, class V>
  static void Serialize(const std::map<K, V>& map, BinaryArchive& archive) {
    try {
      Serialize(static_cast<uint64_t>(map.size()), archive);

      for (const auto& [key, value] : map) {
        Serialize(key, archive);
        Serialize(value, archive);
      }
    } catch (...) {
      throw std::runtime_error("Failed to serialize std::map<K,V>.");
    }
  }

  template <class K, class V>
  static void Serialize(const std::unordered_map<K, V>& umap,
                        BinaryArchive& archive) {
    try {
      Serialize(static_cast<uint64_t>(umap.size()), archive);

      for (const auto& [key, value] : umap) {
        Serialize(key, archive);
        Serialize(value, archive);
      }
    } catch (...) {
      throw std::runtime_error("Failed to serialize std::unordered_map<K,V>.");
    }
  }

  template <class T>
  static void Serialize(const std::set<T>& set, BinaryArchive& archive) {
    try {
      Serialize(static_cast<uint64_t>(set.size()), archive);

      for (const auto& value : set) {
        Serialize(value, archive);
      }
    } catch (...) {
      throw std::runtime_error("Failed to serialize std::set<T>.");
    }
  }

  template <class T>
  static void Serialize(const std::unordered_set<T>& uset,
                        BinaryArchive& archive) {
    try {
      Serialize(static_cast<uint64_t>(uset.size()), archive);

      for (const auto& value : uset) {
        Serialize(value, archive);
      }
    } catch (...) {
      throw std::runtime_error("Failed to serialize std::unordered_set<T>.");
    }
  }

  template <class T>
  static void Serialize(const std::queue<T>& queue, BinaryArchive& archive) {
    try {
      Serialize(static_cast<uint64_t>(queue.size()), archive);

      auto queueCopy = queue;

      while (!queueCopy.empty()) {
        Serialize(queueCopy.front(), archive);
        queueCopy.pop();
      }
    } catch (...) {
      throw std::runtime_error("Failed to serialize std::queue<T>.");
    }
  }

  template <class T>
  static void Serialize(const std::deque<T>& deque, BinaryArchive& archive) {
    try {
      Serialize(static_cast<uint64_t>(deque.size()), archive);

      for (const auto& value : deque) {
        Serialize(value, archive);
      }
    } catch (...) {
      throw std::runtime_error("Failed to serialize std::deque<T>.");
    }
  }

  template <class T>
  static void Serialize(const std::list<T>& list, BinaryArchive& archive) {
    try {
      Serialize(static_cast<uint64_t>(list.size()), archive);

      for (const auto& value : list) {
        Serialize(value, archive);
      }
    } catch (...) {
      throw std::runtime_error("Failed to serialize std::list<T>.");
    }
  }

  template <class T>
  static void Serialize(const std::forward_list<T>& flist,
                        BinaryArchive& archive) {
    try {
      auto initialArchivePosition = archive.GetWritePosition();

      auto size = 0ull;
      Serialize(size, archive);

      for (const auto& value : flist) {
        Serialize(value, archive);
        size++;
      }

      auto currentArchivePosition = archive.GetWritePosition();
      archive.SetWritePosition(initialArchivePosition);

      Serialize(size, archive);

      archive.SetWritePosition(currentArchivePosition);

    } catch (...) {
      throw std::runtime_error("Failed to serialize std::forward_list<T>.");
    }
  }

  template <class T>
  static void Serialize(const std::vector<T>& vector, BinaryArchive& archive) {
    try {
      Serialize(static_cast<uint64_t>(vector.size()), archive);

      for (const auto& value : vector) {
        Serialize(value, archive);
      }
    } catch (...) {
      throw std::runtime_error("Failed to serialize std::vector<T>.");
    }
  }

  template <class T>
  static void Serialize(const std::unique_ptr<T>& pointer,
                        BinaryArchive& archive) {
    auto pointerState = pointer ? PointerState::VALID : PointerState::INVALID;
    Serialize(pointerState, archive);

    if (pointerState == PointerState::VALID) {
      Serialize(*pointer, archive);
    }
  }

  template <class T>
  static void Serialize(const std::shared_ptr<T>& pointer,
                        BinaryArchive& archive) {
    bool stackFrameFlag;
    auto stackFrameMarker = reinterpret_cast<long long>(&stackFrameFlag);
    if (!initialStackFrameMarker) {
      initialStackFrameMarker = stackFrameMarker;
    }

    auto pointerState = pointer ? PointerState::VALID : PointerState::INVALID;
    Serialize(pointerState, archive);

    auto erasedSharedPointer = std::static_pointer_cast<void>(pointer);

    if (pointerState == PointerState::VALID) {
      if (!referenceMap.count(erasedSharedPointer)) {
        referenceMap.emplace(erasedSharedPointer, referenceCount);

        Serialize(referenceCount++, archive);
        Serialize(*pointer, archive);
      } else {
        auto index = referenceMap[erasedSharedPointer];
        Serialize(index, archive);
      }
    }

    if (stackFrameMarker == initialStackFrameMarker) {
      initialStackFrameMarker = 0;
      referenceCount = 0;
      referenceMap.clear();
    }
  }

  template <class T>
  static void Serialize(const std::weak_ptr<T>& pointer,
                        BinaryArchive& archive) {
    auto lockedSharedPointer = pointer.lock();
    if (lockedSharedPointer) {
      Serialize(lockedSharedPointer, archive);
    }
  }

  static void Serialize(const Serializable& object, BinaryArchive& archive) {
    object.Serialize(archive);
  }

  template <class T>
  static void Deserialize(
      T& value, BinaryArchive& archive,
      std::enable_if_t<std::is_integral<T>::value, T>* = nullptr) {
    try {
      T temp = 0;

      archive.Read(reinterpret_cast<unsigned char*>(&temp), sizeof(temp));

      // let's assume that network endian is big
      if (EndiannessProvider::GetSystemEndianness() ==
          EndiannessProvider::Endianness::LITTLE) {
        value = swapBytes(temp);
      } else {
        value = temp;
      }
    } catch (...) {
      throw std::runtime_error("Failed to deserialize integral type value.");
    }
  }

  template <class T>
  static void Deserialize(
      T& value, BinaryArchive& archive,
      std::enable_if_t<std::is_enum<T>::value, T>* = nullptr) {
    try {
      Deserialize(reinterpret_cast<std::underlying_type_t<T>&>(value), archive);
    } catch (...) {
      throw std::runtime_error("Failed to deserialize enum type value.");
    }
  }

  static void Deserialize(std::string& str, BinaryArchive& archive) {
    try {
      auto strSizeInBytes = 0ull;

      Deserialize(strSizeInBytes, archive);

      str.resize(static_cast<std::size_t>(strSizeInBytes));

      archive.Read(reinterpret_cast<unsigned char*>(str.data()),
                   static_cast<std::size_t>(strSizeInBytes));
    } catch (...) {
      throw std::runtime_error("Failed to deserialize std::string.");
    }
  }

  static void Deserialize(std::wstring& wstr, BinaryArchive& archive) {
    try {
      auto strSizeInBytes = 0ull;

      Deserialize(strSizeInBytes, archive);

      wstr.resize(static_cast<std::size_t>(strSizeInBytes / sizeof(wchar_t)));

      archive.Read(reinterpret_cast<unsigned char*>(wstr.data()),
                   static_cast<std::size_t>(strSizeInBytes));
    } catch (...) {
      throw std::runtime_error("Failed to deserialize std::wstring.");
    }
  }

  template <class T1, class T2>
  static void Deserialize(std::pair<T1, T2>& pair, BinaryArchive& archive) {
    try {
      T1&& first{};
      T2&& second{};

      Deserialize(first, archive);
      Deserialize(second, archive);

      pair.first = first;
      pair.second = second;
    } catch (...) {
      throw std::runtime_error("Failed to deserialize std::pair<T1,T2>.");
    }
  }

  template <class T, std::size_t N>
  static void Deserialize(std::array<T, N>& array, BinaryArchive& archive) {
    try {
      for (auto i = 0ull; i < N; i++) {
        T&& value{};
        Deserialize(value, archive);
        array[i] = std::move(value);
      }
    } catch (...) {
      throw std::runtime_error("Failed to deserialize std::array<T,N>.");
    }
  }

  template <class K, class V>
  static void Deserialize(std::map<K, V>& map, BinaryArchive& archive) {
    auto mapSize = 0ull;

    try {
      Deserialize(mapSize, archive);

      for (auto i = 0ull; i < mapSize; i++) {
        K&& key{};
        V&& value{};

        Deserialize(key, archive);
        Deserialize(value, archive);

        map.emplace(std::move(key), std::move(value));
      }
    } catch (...) {
      throw std::runtime_error("Failed to deserialize std::map<K,V>.");
    }
  }

  template <class K, class V>
  static void Deserialize(std::unordered_map<K, V>& umap,
                          BinaryArchive& archive) {
    auto mapSize = 0ull;

    try {
      Deserialize(mapSize, archive);

      for (auto i = 0ull; i < mapSize; i++) {
        K&& key{};
        V&& value{};

        Deserialize(key, archive);
        Deserialize(value, archive);

        umap.emplace(std::move(key), std::move(value));
      }
    } catch (...) {
      throw std::runtime_error(
          "Failed to deserialize std::unordered_map<K,V>.");
    }
  }

  template <class T>
  static void Deserialize(std::set<T>& set, BinaryArchive& archive) {
    auto setSize = 0ull;

    try {
      Deserialize(setSize, archive);

      for (auto i = 0ull; i < setSize; i++) {
        T&& value{};

        Deserialize(value, archive);

        set.emplace(std::move(value));
      }
    } catch (...) {
      throw std::runtime_error("Failed to deserialize std::set<T>.");
    }
  }

  template <class T>
  static void Deserialize(std::unordered_set<T>& uset, BinaryArchive& archive) {
    auto setSize = 0ull;

    try {
      Deserialize(setSize, archive);

      for (auto i = 0ull; i < setSize; i++) {
        T&& value{};

        Deserialize(value, archive);

        uset.emplace(std::move(value));
      }
    } catch (...) {
      throw std::runtime_error("Failed to deserialize std::unordered_set<T>.");
    }
  }

  template <class T>
  static void Deserialize(std::queue<T>& queue, BinaryArchive& archive) {
    auto queueSize = 0ull;

    try {
      Deserialize(queueSize, archive);

      for (auto i = 0ull; i < queueSize; i++) {
        T&& value{};

        Deserialize(value, archive);

        queue.emplace(std::move(value));
      }
    } catch (...) {
      throw std::runtime_error("Failed to deserialize std::queue<T>.");
    }
  }

  template <class T>
  static void Deserialize(std::deque<T>& deque, BinaryArchive& archive) {
    auto dequeSize = 0ull;

    try {
      Deserialize(dequeSize, archive);

      for (auto i = 0ull; i < dequeSize; i++) {
        T&& value{};

        Deserialize(value, archive);

        deque.emplace_back(std::move(value));
      }
    } catch (...) {
      throw std::runtime_error("Failed to deserialize std::deque<T>.");
    }
  }

  template <class T>
  static void Deserialize(std::list<T>& list, BinaryArchive& archive) {
    auto listSize = 0ull;

    try {
      Deserialize(listSize, archive);

      for (auto i = 0ull; i < listSize; i++) {
        T&& value{};

        Deserialize(value, archive);

        list.emplace_back(std::move(value));
      }
    } catch (...) {
      throw std::runtime_error("Failed to deserialize std::list<T>.");
    }
  }

  template <class T>
  static void Deserialize(std::forward_list<T>& flist, BinaryArchive& archive) {
    auto listSize = 0ull;

    try {
      Deserialize(listSize, archive);

      for (auto i = 0ull; i < listSize; i++) {
        T&& value{};

        Deserialize(value, archive);

        flist.emplace_front(std::move(value));
      }

      flist.reverse();

    } catch (...) {
      throw std::runtime_error("Failed to deserialize std::forward_list<T>.");
    }
  }

  template <class T>
  static void Deserialize(std::vector<T>& vector, BinaryArchive& archive) {
    auto vectorSize = 0ull;

    try {
      Deserialize(vectorSize, archive);

      for (auto i = 0ull; i < vectorSize; i++) {
        T&& value{};

        Deserialize(value, archive);

        vector.emplace_back(std::move(value));
      }
    } catch (...) {
      throw std::runtime_error("Failed to deserialize std::vector<T>.");
    }
  }

  template <class T>
  static void Deserialize(std::unique_ptr<T>& pointer, BinaryArchive& archive) {
    auto pointerState = PointerState::NONE;
    Deserialize(pointerState, archive);

    if (pointerState == PointerState::VALID) {
      pointer = std::make_unique<T>();
      Deserialize(*pointer, archive);
    }
  }

  template <class T>
  static void Deserialize(std::shared_ptr<T>& pointer, BinaryArchive& archive) {
    bool stackFrameFlag;
    auto stackFrameMarker = reinterpret_cast<long long>(&stackFrameFlag);
    if (!initialStackFrameMarker) {
      initialStackFrameMarker = stackFrameMarker;
    }

    auto pointerState = PointerState::NONE;
    Deserialize(pointerState, archive);

    if (pointerState == PointerState::VALID) {
      auto index = UNDEFINED_REFERENCE_INDEX;
      Deserialize(index, archive);

      if (!reverseReferenceMap.count(index)) {
        pointer = std::make_shared<T>();

        auto erasedSharedPointer = std::static_pointer_cast<void>(pointer);

        reverseReferenceMap.emplace(index, erasedSharedPointer);

        Deserialize(*pointer, archive);
      } else {
        pointer = std::static_pointer_cast<T>(reverseReferenceMap[index]);
      }
    }

    if (stackFrameMarker == initialStackFrameMarker) {
      initialStackFrameMarker = 0;
      reverseReferenceMap.clear();
    }
  }

  template <class T>
  static void Deserialize(std::weak_ptr<T>& pointer, BinaryArchive& archive) {
    auto lockedSharedPointer = pointer.lock();
    Deserialize(lockedSharedPointer, archive);

    pointer = lockedSharedPointer;
  }

  static void Deserialize(Serializable& object, BinaryArchive& archive) {
    object.Deserialize(archive);
  }

 private:
  template <class T, class Enable = typename std::enable_if<
                         std::is_integral<T>::value>::type>
  static T swapBytes(T value) noexcept {
    T temp = value;

    char *istart = reinterpret_cast<char*>(&temp),
         *iend = istart + sizeof(temp);
    std::reverse(istart, iend);

    return temp;
  }

  static const int UNDEFINED_REFERENCE_INDEX;
  static const int UNDEFINED_OBJECT_UNIQUE_ID;

  enum class PointerState { NONE, VALID, INVALID };

  static thread_local int referenceCount;

  static thread_local long long initialStackFrameMarker;

  static thread_local std::map<std::shared_ptr<void>, int> referenceMap;
  static thread_local std::map<int, std::shared_ptr<void>> reverseReferenceMap;
};
}  // namespace CppUtils
