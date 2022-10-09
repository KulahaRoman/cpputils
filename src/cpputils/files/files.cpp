#include "files.h"

void Files::CreateFile(const fs::path& path) {
  std::ofstream fout;
  fout.exceptions(std::ios_base::badbit | std::ios_base::failbit);
  try {
    fout.open(path, std::ios_base::out);
    fout.close();
  } catch (...) {
#if defined(UNICODE) || defined(_UNICODE)
    throw RuntimeException(L"Failed to create file: " + path.wstring());
#else
    throw RuntimeException("Failed to create file: " + path.string());
#endif
  }
}

void Files::CreateDirectory(const fs::path& path) {
  fs::path absolutePath = fs::absolute(path);

  if (!fs::exists(absolutePath)) {
    try {
      fs::create_directories(absolutePath);
    } catch (...) {
#if defined(UNICODE) || defined(_UNICODE)
      throw RuntimeException(L"Failed to create directory: " +
                             absolutePath.wstring());
#else
      throw RuntimeException("Failed to create directory: " +
                             absolutePath.string());
#endif
    }
  }
}

void Files::Remove(const fs::path& path) {
  try {
    fs::remove_all(path);
  } catch (...) {
#if defined(UNICODE) || defined(_UNICODE)
    throw RuntimeException(L"Failed to remove file/directory: " +
                           path.wstring());
#else
    throw RuntimeException("Failed to remove file/directory: " + path.string());
#endif
  }
}

void Files::Copy(const fs::path& sourcePath, const fs::path& targetPath) {
  try {
    auto&& options = fs::copy_options::overwrite_existing |
                     fs::copy_options::copy_symlinks |
                     fs::copy_options::recursive;

    fs::copy(sourcePath, targetPath, options);
  } catch (...) {
#if defined(UNICODE) || defined(_UNICODE)
    throw RuntimeException(L"Failed to copy file/directory: " +
                           sourcePath.wstring());
#else
    throw RuntimeException("Failed to copy file/directory: " +
                           sourcePath.string());
#endif
  }
}

bool Files::Exists(const fs::path& path) {
  try {
    return fs::exists(path);
  } catch (...) {
#if defined(UNICODE) || defined(_UNICODE)
    throw RuntimeException(L"Failed to check file/directory existence: " +
                           path.wstring());
#else
    throw RuntimeException("Failed to check file/directory existence: " +
                           path.string());
#endif
  }
  return false;
}

uint64_t Files::GetSize(const fs::path& path) {
  try {
    return fs::file_size(path);
  } catch (...) {
#if defined(UNICODE) || defined(_UNICODE)
    throw RuntimeException(L"Failed to get file/directory size: " +
                           path.wstring());
#else
    throw RuntimeException("Failed to get file/directory size: " +
                           path.string());
#endif
  }
  return 0;
}