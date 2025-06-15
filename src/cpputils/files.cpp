#include "files.h"

namespace CppUtils {
void Files::CreateFile(const fs::path& path) {
  std::ofstream fout;
  fout.exceptions(std::ios_base::badbit | std::ios_base::failbit);
  try {
    fout.open(path, std::ios_base::out);
    fout.close();
  } catch (...) {
    throw std::runtime_error("failed to create file: " + path.string());
  }
}

void Files::CreateDirectory(const fs::path& path) {
  fs::path absolutePath = fs::absolute(path);

  if (!fs::exists(absolutePath)) {
    try {
      fs::create_directories(absolutePath);
    } catch (...) {
      throw std::runtime_error("failed to create directory: " +
                               absolutePath.string());
    }
  }
}

void Files::Remove(const fs::path& path) {
  try {
    fs::remove_all(path);
  } catch (...) {
    throw std::runtime_error("failed to remove file/directory: " +
                             path.string());
  }
}

void Files::Copy(const fs::path& sourcePath, const fs::path& targetPath) {
  try {
    auto&& options = fs::copy_options::overwrite_existing |
                     fs::copy_options::copy_symlinks |
                     fs::copy_options::recursive;

    fs::copy(sourcePath, targetPath, options);
  } catch (...) {
    throw std::runtime_error("failed to copy file/directory: " +
                             sourcePath.string());
  }
}

bool Files::Exists(const fs::path& path) {
  try {
    return fs::exists(path);
  } catch (...) {
    throw std::runtime_error("failed to check file/directory existence: " +
                             path.string());
  }
  return false;
}

uint64_t Files::GetSize(const fs::path& path) {
  try {
    return fs::file_size(path);
  } catch (...) {
    throw std::runtime_error("failed to get file/directory size: " +
                             path.string());
  }
  return 0;
}
}  // namespace CppUtils
