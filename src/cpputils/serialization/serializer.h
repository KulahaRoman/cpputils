#pragma once
#include <algorithm>
#include <list>
#include <map>
#include <memory>
#include <set>
#include <span>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <vector>

#include "serializable.h"

class Serializer {
 public:
  template <class T, class Enable = typename std::enable_if<
                         std::is_integral<T>::value>::type>
  static const uint64_t Serialize(const T value,
                                  std::vector<unsigned char>& binary) {
    auto oldSize = binary.size();

    binary.insert(
        binary.end(), reinterpret_cast<const unsigned char*>(&value),
        reinterpret_cast<const unsigned char*>(&value) + sizeof(value));

    auto newSize = binary.size();

    return newSize - oldSize;
  }

  static uint64_t Serialize(const std::string& str,
                            std::vector<unsigned char>& binary) {
    auto oldSize = binary.size();

    Serialize(static_cast<uint64_t>(str.size()), binary);

    binary.insert(
        binary.end(), reinterpret_cast<const unsigned char*>(str.data()),
        reinterpret_cast<const unsigned char*>(str.data()) + str.size());

    auto newSize = binary.size();

    return newSize - oldSize;
  }

  static uint64_t Serialize(const std::wstring& str,
                            std::vector<unsigned char>& binary) {
    auto oldSize = binary.size();

    Serialize(static_cast<uint64_t>(str.size() * sizeof(wchar_t)), binary);

    binary.insert(binary.end(),
                  reinterpret_cast<const unsigned char*>(str.data()),
                  reinterpret_cast<const unsigned char*>(str.data()) +
                      str.size() * sizeof(wchar_t));

    auto newSize = binary.size();

    return newSize - oldSize;
  }

  template <class K, class V>
  static uint64_t Serialize(const std::map<K, V>& map,
                            std::vector<unsigned char>& binary) {
    auto oldSize = binary.size();

    Serialize(static_cast<uint64_t>(map.size()), binary);

    for (const auto& [key, value] : map) {
      Serialize(key, binary);
      Serialize(value, binary);
    }

    auto newSize = binary.size();

    return newSize - oldSize;
  }

  template <class T>
  static uint64_t Serialize(const std::set<T>& set,
                            std::vector<unsigned char>& binary) {
    auto oldSize = binary.size();

    Serialize(static_cast<uint64_t>(set.size()));

    for (const auto& value : set) {
      Serialize(value, binary);
    }

    auto newSize = binary.size();

    return newSize - oldSize;
  }

  template <class T>
  static uint64_t Serialize(const std::list<T>& list,
                            std::vector<unsigned char>& binary) {
    auto oldSize = binary.size();

    Serialize(static_cast<uint64_t>(list.size()));

    for (const auto& value : list) {
      Serialize(value, binary);
    }

    auto newSize = binary.size();

    return newSize - oldSize;
  }

  template <class T>
  static uint64_t Serialize(const std::vector<T>& vector,
                            std::vector<unsigned char>& binary) {
    auto oldSize = binary.size();

    Serialize(static_cast<uint64_t>(vector.size()), binary);

    for (const auto& value : vector) {
      Serialize(value, binary);
    }

    auto newSize = binary.size();

    return newSize - oldSize;
  }

  template <class T>
  static uint64_t Serialize(const std::shared_ptr<T>& obj,
                            std::vector<unsigned char>& binary) {
    if (!obj) {
      throw std::runtime_error(
          "Failed to serialize std::shared_ptr<T>: pointer is null.");
    }

    return Serialize(*obj, binary);
  }

  static uint64_t Serialize(const Serializable& obj,
                            std::vector<unsigned char>& binary) {
    return obj.Serialize(binary);
  }

  template <class T, class Enable = typename std::enable_if<
                         std::is_integral<T>::value>::type>
  static uint64_t Deserialize(T& value,
                              const std::span<unsigned char>& binary) {
    std::copy(
        reinterpret_cast<const unsigned char*>(binary.data()),
        reinterpret_cast<const unsigned char*>(binary.data() + sizeof(value)),
        reinterpret_cast<unsigned char*>(&value));

    return sizeof(value);
  }

  static uint64_t Deserialize(std::string& str,
                              const std::span<unsigned char>& binary) {
    auto strSize = 0ull;
    Deserialize(strSize, binary);

    str.insert(str.begin(),
               reinterpret_cast<const char*>(binary.data() + sizeof(strSize)),
               reinterpret_cast<const char*>(binary.data() + sizeof(strSize)) +
                   strSize);

    return strSize + sizeof(strSize);
  }

  static uint64_t Deserialize(std::wstring& str,
                              const std::span<unsigned char>& binary) {
    auto strSize = 0ull;
    Deserialize(strSize, binary);

    str.insert(
        str.begin(),
        reinterpret_cast<const wchar_t*>(binary.data() + sizeof(strSize)),
        reinterpret_cast<const wchar_t*>(binary.data() + sizeof(strSize)) +
            strSize / sizeof(wchar_t));

    return strSize + sizeof(strSize);
  }

  template <class K, class V>
  static uint64_t Deserialize(std::map<K, V>& map,
                              const std::span<unsigned char>& binary) {
    auto nBytes = 0ull;

    auto mapSize = 0ull;
    nBytes += Deserialize(mapSize, binary);

    for (auto i = 0ull; i < mapSize; i++) {
      K&& key{};
      V&& value{};

      nBytes +=
          Deserialize(key, std::span(binary.begin() + nBytes, binary.end()));
      nBytes +=
          Deserialize(value, std::span(binary.begin() + nBytes, binary.end()));

      map.emplace(std::move(key), std::move(value));
    }

    return nBytes;
  }

  template <class T>
  static uint64_t Deserialize(std::set<T>& set,
                              const std::span<unsigned char>& binary) {
    auto nBytes = 0ull;

    auto setSize = 0ull;
    nBytes += Deserialize(setSize, binary);

    for (auto i = 0ull; i < setSize; i++) {
      T&& value{};

      nBytes +=
          Deserialize(value, std::span(binary.begin() + nBytes, binary.end()));

      set.emplace(std::move(value));
    }

    return nBytes;
  }

  template <class T>
  static uint64_t Deserialize(std::list<T>& list,
                              const std::span<unsigned char>& binary) {
    auto nBytes = 0ull;

    auto listSize = 0ull;
    nBytes += Deserialize(listSize, binary);

    for (auto i = 0ull; i < listSize; i++) {
      T&& value{};

      nBytes +=
          Deserialize(value, std::span(binary.begin() + nBytes, binary.end()));

      list.emplace_back(std::move(value));
    }

    return nBytes;
  }

  template <class T>
  static uint64_t Deserialize(std::vector<T>& vector,
                              const std::span<unsigned char>& binary) {
    auto nBytes = 0ull;

    auto vectorSize = 0ull;
    nBytes += Deserialize(vectorSize, binary);

    for (auto i = 0ull; i < vectorSize; i++) {
      T&& value{};

      nBytes +=
          Deserialize(value, std::span(binary.begin() + nBytes, binary.end()));

      vector.emplace_back(std::move(value));
    }

    return nBytes;
  }

  template <class T>
  static uint64_t Deserialize(std::shared_ptr<T>& obj,
                              const std::span<unsigned char>& binary) {
    if (!obj) {
      obj = std::make_shared<T>();
    }

    return Deserialize(*obj, binary);
  }

  static uint64_t Deserialize(Serializable& obj,
                              const std::span<unsigned char>& binary) {
    return obj.Deserialize(binary);
  }
};
