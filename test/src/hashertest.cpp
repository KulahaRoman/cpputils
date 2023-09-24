#include <cpputils/md5hasher.h>
#include <cpputils/sha256hasher.h>
#include <gtest/gtest.h>

using namespace CppUtils::Hashing;

TEST(HasherTest, MD5) {
  std::string strToHash{"Hello, World!"};
  std::vector<unsigned char> bytesToHash{strToHash.begin(), strToHash.end()};

  auto hasher = std::make_unique<MD5Hasher>();
  auto hash = hasher->Hash(bytesToHash);

  unsigned char preHashBytes[17] =
      "\x65\xa8\xe2\x7d\x88\x79\x28\x38\x31\xb6\x64\xbd\x8b\x7f\x0a\xd4";

  std::vector<unsigned char> preHash{
      reinterpret_cast<unsigned char*>(&preHashBytes),
      reinterpret_cast<unsigned char*>(&preHashBytes) + 16};

  ASSERT_TRUE(hash == preHash);
}

TEST(HasherTest, SHA256) {
  std::string strToHash{"Hello, World!"};
  std::vector<unsigned char> bytesToHash{strToHash.begin(), strToHash.end()};

  auto hasher = std::make_unique<SHA256Hasher>();
  auto hash = hasher->Hash(bytesToHash);

  unsigned char preHashBytes[33] =
      "\xdf\xfd\x60\x21\xbb\x2b\xd5\xb0\xaf\x67\x62\x90\x80\x9e\xc3\xa5\x31\x91"
      "\xdd\x81\xc7\xf7\x0a\x4b\x28\x68\x8a\x36\x21\x82\x98\x6f";

  std::vector<unsigned char> preHash{
      reinterpret_cast<unsigned char*>(&preHashBytes),
      reinterpret_cast<unsigned char*>(&preHashBytes) + 32};

  ASSERT_TRUE(hash == preHash);
}
