#include "files.h"

void Files::Create(const
#if defined(UNICODE) || defined(_UNICODE)
                   std::wstring
#else
                   std::string
#endif
                       & file) {
  std::ofstream fout;
  fout.exceptions(std::ios_base::badbit | std::ios_base::failbit);
  try {
    fout.open(file, std::ios_base::out);
    fout.close();
  } catch (...) {
#if defined(UNICODE) || defined(_UNICODE)
    throw RuntimeException(L"Failed to create file: " + file);
#else
    throw RuntimeException("Failed to create file: " + file);
#endif
  }
}

void Files::Delete(const
#if defined(UNICODE) || defined(_UNICODE)
                   std::wstring
#else
                   std::string
#endif
                       & file) {
  try {
    fs::remove(file);
  } catch (...) {
#if defined(UNICODE) || defined(_UNICODE)
    throw RuntimeException(L"Failed to delete file: " + file);
#else
    throw RuntimeException("Failed to delete file: " + file);
#endif
  }
}

void Files::Copy(const
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
                     & target) {
  try {
    fs::copy_file(source, target);
  } catch (...) {
#if defined(UNICODE) || defined(_UNICODE)
    throw RuntimeException(L"Failed to copy file: " + source);
#else
    throw RuntimeException("Failed to copy file: " + source);
#endif
  }
}

bool Files::Exists(const
#if defined(UNICODE) || defined(_UNICODE)
                   std::wstring
#else
                   std::string
#endif
                       & file) {
  try {
    return fs::exists(file);
  } catch (...) {
#if defined(UNICODE) || defined(_UNICODE)
    throw RuntimeException(L"Failed to cheñk file existence: " + file);
#else
    throw RuntimeException("Failed to cheñk file existence: " + file);
#endif
  }
  return false;
}

uint64_t Files::GetSize(const
#if defined(UNICODE) || defined(_UNICODE)
                        std::wstring
#else
                        std::string
#endif
                            & file) {
  try {
    return fs::file_size(file);
  } catch (...) {
#if defined(UNICODE) || defined(_UNICODE)
    throw RuntimeException(L"Failed to get file size: " + file);
#else
    throw RuntimeException("Failed to get file size: " + file);
#endif
  }
  return 0;
}
