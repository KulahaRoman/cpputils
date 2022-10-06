#pragma once
#include <filesystem>
#include <fstream>

#include "../exceptions/exceptions.h"

namespace fs = std::filesystem;

class Files {
 public:
  static void Create(const
#if defined(UNICODE) || defined(_UNICODE)
                     std::wstring
#else
                     std::string
#endif
                         & file);
  static void Delete(const
#if defined(UNICODE) || defined(_UNICODE)
                     std::wstring
#else
                     std::string
#endif
                         & file);
  static void Copy(const
#if defined(UNICODE) || defined(_UNICODE)
                   std::wstring
#else
                   std::string
#endif
                       & source,
                   const
#if defined(UNICODE) || defined(_UNICODE)
                   std::wstring
#else
                   std::string
#endif
                       & target);
  static bool Exists(const
#if defined(UNICODE) || defined(_UNICODE)
                     std::wstring
#else
                     std::string
#endif
                         & file);
  static uint64_t GetSize(const
#if defined(UNICODE) || defined(_UNICODE)
                          std::wstring
#else
                          std::string
#endif
                              & file);
};
