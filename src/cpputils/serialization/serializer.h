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
#include "serializable.h"

class Serializer {
 public:
  template <class T, class Enable = typename std::enable_if<
                         std::is_integral<T>::value>::type>
  static void Serialize(const T value, BinaryArchive& archive) {
    try {
      // let's assume that network endian is big
      T temp = value;
      if constexpr (std::endian::native == std::endian::little) {
        std::reverse(&temp, &temp + sizeof(temp));
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
    obj.Serialize(archive);
  }

  template <class T, class Enable = typename std::enable_if<
                         std::is_integral<T>::value>::type>
  static void Deserialize(T& value, BinaryArchive& archive) {
    try {
      T temp = 0;

      archive.Read(reinterpret_cast<unsigned char*>(&temp), sizeof(temp));

      // let's assume that network endian is big
      if constexpr (std::endian::native == std::endian::little) {
        std::reverse(&temp, &temp + sizeof(temp));
      }

      value = temp;

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
    obj.Deserialize(archive);
  }

 private:
  template <class T, class Enable = typename std::enable_if<
                         std::is_integral<T>::value>::type>
  T serializeWithEndianness(const T& value) {}
};
