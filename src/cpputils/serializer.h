#pragma once
#include <algorithm>
#include <list>
#include <map>
#include <memory>
#include <set>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <vector>

#include "binaryarchive.h"
#include "endiannessprovider.h"
#include "serializable.h"

namespace CppUtils {
class Serializer {
 public:
  template <class T, class Enable = typename std::enable_if<
                         std::is_integral<T>::value>::type>
  static void Serialize(const T value, BinaryArchive& archive) {
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

  static void Serialize(const std::wstring& str, BinaryArchive& archive) {
    try {
      auto strSizeInBytes = static_cast<uint64_t>(str.size() * sizeof(wchar_t));

      Serialize(strSizeInBytes, archive);

      archive.Write(reinterpret_cast<const unsigned char*>(str.data()),
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
  static void Serialize(const std::shared_ptr<T>& obj, BinaryArchive& archive) {
    if (!obj) {
      throw std::runtime_error(
          "Failed to serialize std::shared_ptr<T>: pointer is null.");
    }
    Serialize(*obj, archive);
  }

  static void Serialize(const Serializable& obj, BinaryArchive& archive) {
    // If serializable object 'obj' was not serialized earlier,
    // put it into reference map and increment 'objectCount', then actually
    // serialize.
    if (!referenceMap.count(&obj)) {
      referenceMap.emplace(&obj, objectCount);

      Serialize(objectCount++, archive);

      auto serialUID = obj.GetSerialUID();
      Serialize(serialUID, archive);

      obj.Serialize(archive);
    } else {
      auto index = referenceMap[&obj];
      Serialize(index, archive);
    }

    // The end of serializable objects tree, clear reference map and object
    // counter.
    if (referenceMap.count(&obj)) {
      auto index = referenceMap[&obj];
      if (index == 0) {
        objectCount = 0;
        referenceMap.clear();
      }
    }
  }

  template <class T, class Enable = typename std::enable_if<
                         std::is_integral<T>::value>::type>
  static void Deserialize(T& value, BinaryArchive& archive) {
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

  static void Deserialize(std::wstring& str, BinaryArchive& archive) {
    try {
      auto strSizeInBytes = 0ull;

      Deserialize(strSizeInBytes, archive);

      str.resize(static_cast<std::size_t>(strSizeInBytes / sizeof(wchar_t)));

      archive.Read(reinterpret_cast<unsigned char*>(str.data()),
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
  static void Deserialize(std::shared_ptr<T>& obj, BinaryArchive& archive) {
    if (!obj) {
      obj = std::make_shared<T>();
    }

    Deserialize(*obj, archive);
  }

  static void Deserialize(Serializable& obj, BinaryArchive& archive) {
    // Read reference index of serializable object.
    auto index = UNDEFINED_REFERENCE_INDEX;
    Deserialize(index, archive);

    // If there is no object with such reference index in reference map,
    // deserialize it and put into reference map.
    if (!reverseReferenceMap.count(index)) {
      // Read & check unique serial ID.
      auto serialUID = UNDEFINED_OBJECT_UNIQUE_ID;
      Deserialize(serialUID, archive);

      if (serialUID != obj.GetSerialUID()) {
        throw std::runtime_error(
            "Failed to deserialize object (wrong UID or corrupted data).");
      }

      reverseReferenceMap.emplace(index, &obj);
      obj.Deserialize(archive);
    } else {
      // If there is already an object with such reference index, don't
      // deserialize it again, just assign a copy of an previously deserialized
      // object via copy assignment operator.
      obj = *reverseReferenceMap[index];
    }

    // The end of object tree, clearing reference map.
    if (index == 0) {
      reverseReferenceMap.clear();
    }
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

  // Private const definitions.
  static const int UNDEFINED_REFERENCE_INDEX;
  static const int UNDEFINED_OBJECT_UNIQUE_ID;

  // Thread-local reference maps and object counter.

  // Used for serialization.
  static thread_local int objectCount;
  // Used for serialization.
  static thread_local std::map<const Serializable*, int> referenceMap;
  // Used for deserialization.
  static thread_local std::map<int, const Serializable*> reverseReferenceMap;
};
}  // namespace CppUtils
