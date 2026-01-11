#include "files.h"

namespace CppUtils {
void Files::CreateFile(const fs::path& path) {
  std::ofstream fout;
  fout.exceptions(std::ios_base::badbit | std::ios_base::failbit);
  try {
    fout.open(path, std::ios_base::out);
    fout.close();
  } catch (const std::exception& e) {
    throw std::runtime_error("failed to create file " + path.string() + ": " +
                             e.what());
  }
}

void Files::CreateDirectory(const fs::path& path) {
  fs::path absolutePath = fs::absolute(path);

  if (!fs::exists(absolutePath)) {
    try {
      fs::create_directories(absolutePath);
    } catch (const std::exception& e) {
      throw std::runtime_error("failed to create directory " +
                               absolutePath.string() + ": " + e.what());
    }
  }
}

void Files::Remove(const fs::path& path) {
  try {
    fs::remove_all(path);
  } catch (const std::exception& e) {
    throw std::runtime_error("failed to remove file/directory " +
                             path.string() + ": " + e.what());
  }
}

void Files::Copy(const fs::path& sourcePath, const fs::path& targetPath) {
  try {
    auto&& options = fs::copy_options::overwrite_existing |
                     fs::copy_options::copy_symlinks |
                     fs::copy_options::recursive;

    fs::copy(sourcePath, targetPath, options);
  } catch (const std::exception& e) {
    throw std::runtime_error("failed to copy file/directory " +
                             sourcePath.string() + ": " + e.what());
  }
}

bool Files::Exists(const fs::path& path) {
  try {
    return fs::exists(path);
  } catch (const std::exception& e) {
    throw std::runtime_error("failed to check file/directory existence " +
                             path.string() + ": " + e.what());
  }
  return false;
}

uint64_t Files::GetSize(const fs::path& path) {
  try {
    return fs::file_size(path);
  } catch (const std::exception& e) {
    throw std::runtime_error("failed to get file/directory size: " +
                             path.string() + ": " + e.what());
  }
  return 0;
}
}  // namespace CppUtils
