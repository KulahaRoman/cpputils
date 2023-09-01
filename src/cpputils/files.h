#pragma once
#include <filesystem>
#include <fstream>
#include <stdexcept>

#ifdef _WIN32
#undef CreateFile
#undef CreateDirectory
#undef CopyFile
#endif

namespace fs = std::filesystem;

class Files {
 public:
  static void CreateFile(const fs::path& path);
  static void CreateDirectory(const fs::path& path);
  static void Remove(const fs::path& path);
  static void Copy(const fs::path& sourcePath, const fs::path& targetPath);
  static bool Exists(const fs::path& path);
  static uint64_t GetSize(const fs::path& path);
};
