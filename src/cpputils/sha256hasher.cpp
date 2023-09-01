#include "sha256hasher.h"

std::vector<unsigned char> SHA256Hasher::Hash(
    const std::vector<unsigned char>& data) const {
  SHA256 sha256;
  return sha256.result(data);
}
