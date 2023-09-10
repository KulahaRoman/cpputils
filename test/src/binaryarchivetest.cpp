#include <cpputils/binaryarchive.h>
#include <gtest/gtest.h>

TEST(BinaryArchiveTest, SizeAfterDefaultConstruction) {
  CppUtils::BinaryArchive archive;
  ASSERT_EQ(archive.GetSize(), 0);
}

TEST(BinaryArchiveTest, SizeAfterBytesWrittenThenClear) {
  CppUtils::BinaryArchive archive;
  std::string bytes(50, '0');
  archive.Write(reinterpret_cast<const unsigned char*>(bytes.data()),
                bytes.size());
  ASSERT_EQ(archive.GetSize(), 50);
  archive.Clear();
  ASSERT_EQ(archive.GetSize(), 0);
}

TEST(BinaryArchiveTest, Write50BytesWrite1Byte) {
  CppUtils::BinaryArchive archive;
  std::string bytes(50, '0');
  archive.Write(reinterpret_cast<const unsigned char*>(bytes.data()),
                bytes.size());
  ASSERT_EQ(archive.GetSize(), 50);
  archive.Write(reinterpret_cast<const unsigned char*>(bytes.data()), 1);
  ASSERT_EQ(archive.GetSize(), 51);
}

TEST(BinaryArchiveTest, WriteBytesSeekWriteDirectionWriteBytes) {
  CppUtils::BinaryArchive archive;
  std::string bytesOne(50, '0');
  archive.Write(reinterpret_cast<const unsigned char*>(bytesOne.data()),
                bytesOne.size());
  ASSERT_EQ(archive.GetSize(), 50);
  archive.SetWritePosition(-25,
                           CppUtils::BinaryArchive::SeekDirection::RELATIVE);
  std::string bytesTwo(50, '1');
  archive.Write(reinterpret_cast<const unsigned char*>(bytesTwo.data()),
                bytesTwo.size());
  ASSERT_EQ(archive.GetSize(), 75);
}

TEST(BinaryArchiveTest, WriteBytesSeekWriteDirectionByOneWriteOneByte) {
  CppUtils::BinaryArchive archive;
  std::string bytesOne(50, '0');
  archive.Write(reinterpret_cast<const unsigned char*>(bytesOne.data()),
                bytesOne.size());
  ASSERT_EQ(archive.GetSize(), 50);
  archive.SetWritePosition(-1,
                           CppUtils::BinaryArchive::SeekDirection::RELATIVE);
  std::string bytesTwo(1, '1');
  archive.Write(reinterpret_cast<const unsigned char*>(bytesTwo.data()),
                bytesTwo.size());
  ASSERT_EQ(archive.GetSize(), 50);
}

TEST(BinaryArchiveTest, WriteBytesSeekWriteDirectionByOneWriteTwoBytes) {
  CppUtils::BinaryArchive archive;
  std::string bytesOne(50, '0');
  archive.Write(reinterpret_cast<const unsigned char*>(bytesOne.data()),
                bytesOne.size());
  ASSERT_EQ(archive.GetSize(), 50);
  archive.SetWritePosition(-1,
                           CppUtils::BinaryArchive::SeekDirection::RELATIVE);
  std::string bytesTwo(2, '1');
  archive.Write(reinterpret_cast<const unsigned char*>(bytesTwo.data()),
                bytesTwo.size());
  ASSERT_EQ(archive.GetSize(), 51);
}

TEST(BinaryArchiveTest, WriteBytesSeekWriteDirFromEndByTwoBytesWriteFiveBytes) {
  CppUtils::BinaryArchive archive;
  std::string bytesOne(50, '0');
  archive.Write(reinterpret_cast<const unsigned char*>(bytesOne.data()),
                bytesOne.size());
  ASSERT_EQ(archive.GetSize(), 50);
  archive.SetWritePosition(2, CppUtils::BinaryArchive::SeekDirection::END);
  std::string bytesTwo(5, '1');
  archive.Write(reinterpret_cast<const unsigned char*>(bytesTwo.data()),
                bytesTwo.size());
  ASSERT_EQ(archive.GetSize(), 50 - 2 + 5);
}

TEST(BinaryArchiveTest, EmptyArchiveSeekWriteDirectionMinus1Relative) {
  CppUtils::BinaryArchive archive;
  EXPECT_THROW(archive.SetWritePosition(
                   -1, CppUtils::BinaryArchive::SeekDirection::RELATIVE),
               std::runtime_error);
}

TEST(BinaryArchiveTest, EmptyArchiveSeekWriteDirection1Relative) {
  CppUtils::BinaryArchive archive;
  EXPECT_THROW(archive.SetWritePosition(
                   1, CppUtils::BinaryArchive::SeekDirection::RELATIVE),
               std::runtime_error);
}

TEST(BinaryArchiveTest, EmptyArchiveSeekWriteDirection1End) {
  CppUtils::BinaryArchive archive;
  EXPECT_THROW(
      archive.SetWritePosition(1, CppUtils::BinaryArchive::SeekDirection::END),
      std::runtime_error);
}

TEST(BinaryArchiveTest, EmptyArchiveSeekWriteDirectionMinus1End) {
  CppUtils::BinaryArchive archive;
  EXPECT_THROW(
      archive.SetWritePosition(-1, CppUtils::BinaryArchive::SeekDirection::END),
      std::runtime_error);
}

TEST(BinaryArchiveTest, EmptyArchiveSeekWriteDirection1Begin) {
  CppUtils::BinaryArchive archive;
  EXPECT_THROW(archive.SetWritePosition(
                   1, CppUtils::BinaryArchive::SeekDirection::BEGIN),
               std::runtime_error);
}

TEST(BinaryArchiveTest, EmptyArchiveSeekWriteDirectionMinus1Begin) {
  CppUtils::BinaryArchive archive;
  EXPECT_THROW(archive.SetWritePosition(
                   -1, CppUtils::BinaryArchive::SeekDirection::BEGIN),
               std::runtime_error);
}

TEST(BinaryArchiveTest, WriteTextRead3BytesFromEndTwoTimes) {
  CppUtils::BinaryArchive archive;
  std::string inStr{"1234567890"};
  archive.Write(reinterpret_cast<const unsigned char*>(inStr.data()),
                inStr.size());
  archive.SetReadPosition(3, CppUtils::BinaryArchive::SeekDirection::END);
  std::string outStr(3, '0');
  archive.Read(reinterpret_cast<unsigned char*>(outStr.data()), 3);
  ASSERT_STREQ(outStr.data(), "890");

  archive.SetWritePosition(2, CppUtils::BinaryArchive::SeekDirection::END);

  archive.Write(reinterpret_cast<const unsigned char*>(inStr.data()),
                inStr.size());
  archive.SetReadPosition(3, CppUtils::BinaryArchive::SeekDirection::END);
  archive.Read(reinterpret_cast<unsigned char*>(outStr.data()), 3);
  ASSERT_STREQ(outStr.data(), "890");
}

TEST(BinaryArchiveTest,
     WriteTextSeekRead5BytesEndRead2BytesWrite11BytesSeek3EndRead3Bytes) {
  CppUtils::BinaryArchive archive;
  std::string inStr{"1234567890"};
  archive.Write(reinterpret_cast<const unsigned char*>(inStr.data()),
                inStr.size());
  archive.SetReadPosition(5, CppUtils::BinaryArchive::SeekDirection::END);
  std::string outStr(2, '0');
  archive.Read(reinterpret_cast<unsigned char*>(outStr.data()), 2);
  ASSERT_STREQ(outStr.data(), "67");

  archive.Write(reinterpret_cast<const unsigned char*>(inStr.data()),
                inStr.size());
  archive.SetReadPosition(3, CppUtils::BinaryArchive::SeekDirection::END);
  archive.Read(reinterpret_cast<unsigned char*>(outStr.data()), 3);
  ASSERT_STREQ(outStr.data(), "890");
}

TEST(BinaryArchiveTest, EmptyArchiveSeekReadDirOneByteFromBegin) {
  CppUtils::BinaryArchive archive;
  EXPECT_THROW(
      archive.SetReadPosition(1, CppUtils::BinaryArchive::SeekDirection::BEGIN),
      std::runtime_error);
}

TEST(BinaryArchiveTest, EmptyArchiveSeekReadDirMinusOneByteFromBegin) {
  CppUtils::BinaryArchive archive;
  EXPECT_THROW(archive.SetReadPosition(
                   -1, CppUtils::BinaryArchive::SeekDirection::BEGIN),
               std::runtime_error);
}

TEST(BinaryArchiveTest, EmptyArchiveSeekReadDirOneByteFromEnd) {
  CppUtils::BinaryArchive archive;
  EXPECT_THROW(
      archive.SetReadPosition(1, CppUtils::BinaryArchive::SeekDirection::END),
      std::runtime_error);
}

TEST(BinaryArchiveTest, EmptyArchiveSeekReadDirMinusOneByteFromEnd) {
  CppUtils::BinaryArchive archive;
  EXPECT_THROW(
      archive.SetReadPosition(-1, CppUtils::BinaryArchive::SeekDirection::END),
      std::runtime_error);
}

TEST(BinaryArchiveTest, EmptyArchiveSeekReadDirOneByteFromRelative) {
  CppUtils::BinaryArchive archive;
  EXPECT_THROW(archive.SetReadPosition(
                   1, CppUtils::BinaryArchive::SeekDirection::RELATIVE),
               std::runtime_error);
}

TEST(BinaryArchiveTest, EmptyArchiveSeekReadDirMinusOneByteFromRelative) {
  CppUtils::BinaryArchive archive;
  EXPECT_THROW(archive.SetReadPosition(
                   -1, CppUtils::BinaryArchive::SeekDirection::RELATIVE),
               std::runtime_error);
}
