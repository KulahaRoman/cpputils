#include <cpputils/binaryarchive.h>
#include <gtest/gtest.h>

using namespace CppUtils::Serialization;

TEST(BinaryArchiveTest, SizeAfterDefaultConstruction) {
  BinaryArchive archive;
  ASSERT_EQ(archive.GetSize(), 0);
}

TEST(BinaryArchiveTest, SizeAfterBytesWrittenThenClear) {
  BinaryArchive archive;
  std::string bytes(50, '0');
  archive.Write(reinterpret_cast<const unsigned char*>(bytes.data()),
                bytes.size());
  ASSERT_EQ(archive.GetSize(), 50);
  archive.Clear();
  ASSERT_EQ(archive.GetSize(), 0);
}

TEST(BinaryArchiveTest, Write50BytesWrite1Byte) {
  BinaryArchive archive;
  std::string bytes(50, '0');
  archive.Write(reinterpret_cast<const unsigned char*>(bytes.data()),
                bytes.size());
  ASSERT_EQ(archive.GetSize(), 50);
  archive.Write(reinterpret_cast<const unsigned char*>(bytes.data()), 1);
  ASSERT_EQ(archive.GetSize(), 51);
}

TEST(BinaryArchiveTest, WriteBytesSeekWriteDirectionWriteBytes) {
  BinaryArchive archive;
  std::string bytesOne(50, '0');
  archive.Write(reinterpret_cast<const unsigned char*>(bytesOne.data()),
                bytesOne.size());
  ASSERT_EQ(archive.GetSize(), 50);
  archive.SetWritePosition(-25, BinaryArchive::SeekDirection::RELATIVE);
  std::string bytesTwo(50, '1');
  archive.Write(reinterpret_cast<const unsigned char*>(bytesTwo.data()),
                bytesTwo.size());
  ASSERT_EQ(archive.GetSize(), 75);
}

TEST(BinaryArchiveTest, WriteBytesSeekWriteDirectionByOneWriteOneByte) {
  BinaryArchive archive;
  std::string bytesOne(50, '0');
  archive.Write(reinterpret_cast<const unsigned char*>(bytesOne.data()),
                bytesOne.size());
  ASSERT_EQ(archive.GetSize(), 50);
  archive.SetWritePosition(-1, BinaryArchive::SeekDirection::RELATIVE);
  std::string bytesTwo(1, '1');
  archive.Write(reinterpret_cast<const unsigned char*>(bytesTwo.data()),
                bytesTwo.size());
  ASSERT_EQ(archive.GetSize(), 50);
}

TEST(BinaryArchiveTest, WriteBytesSeekWriteDirectionByOneWriteTwoBytes) {
  BinaryArchive archive;
  std::string bytesOne(50, '0');
  archive.Write(reinterpret_cast<const unsigned char*>(bytesOne.data()),
                bytesOne.size());
  ASSERT_EQ(archive.GetSize(), 50);
  archive.SetWritePosition(-1, BinaryArchive::SeekDirection::RELATIVE);
  std::string bytesTwo(2, '1');
  archive.Write(reinterpret_cast<const unsigned char*>(bytesTwo.data()),
                bytesTwo.size());
  ASSERT_EQ(archive.GetSize(), 51);
}

TEST(BinaryArchiveTest, WriteBytesSeekWriteDirFromEndByTwoBytesWriteFiveBytes) {
  BinaryArchive archive;
  std::string bytesOne(50, '0');
  archive.Write(reinterpret_cast<const unsigned char*>(bytesOne.data()),
                bytesOne.size());
  ASSERT_EQ(archive.GetSize(), 50);
  archive.SetWritePosition(2, BinaryArchive::SeekDirection::END);
  std::string bytesTwo(5, '1');
  archive.Write(reinterpret_cast<const unsigned char*>(bytesTwo.data()),
                bytesTwo.size());
  ASSERT_EQ(archive.GetSize(), 50 - 2 + 5);
}

TEST(BinaryArchiveTest, EmptyArchiveSeekWriteDirectionMinus1Relative) {
  BinaryArchive archive;
  EXPECT_THROW(
      archive.SetWritePosition(-1, BinaryArchive::SeekDirection::RELATIVE),
      std::runtime_error);
}

TEST(BinaryArchiveTest, EmptyArchiveSeekWriteDirection1Relative) {
  BinaryArchive archive;
  EXPECT_THROW(
      archive.SetWritePosition(1, BinaryArchive::SeekDirection::RELATIVE),
      std::runtime_error);
}

TEST(BinaryArchiveTest, EmptyArchiveSeekWriteDirection1End) {
  BinaryArchive archive;
  EXPECT_THROW(archive.SetWritePosition(1, BinaryArchive::SeekDirection::END),
               std::runtime_error);
}

TEST(BinaryArchiveTest, EmptyArchiveSeekWriteDirectionMinus1End) {
  BinaryArchive archive;
  EXPECT_THROW(archive.SetWritePosition(-1, BinaryArchive::SeekDirection::END),
               std::runtime_error);
}

TEST(BinaryArchiveTest, EmptyArchiveSeekWriteDirection1Begin) {
  BinaryArchive archive;
  EXPECT_THROW(archive.SetWritePosition(1, BinaryArchive::SeekDirection::BEGIN),
               std::runtime_error);
}

TEST(BinaryArchiveTest, EmptyArchiveSeekWriteDirectionMinus1Begin) {
  BinaryArchive archive;
  EXPECT_THROW(
      archive.SetWritePosition(-1, BinaryArchive::SeekDirection::BEGIN),
      std::runtime_error);
}

TEST(BinaryArchiveTest, WriteTextRead3BytesFromEndTwoTimes) {
  BinaryArchive archive;
  std::string inStr{"1234567890"};

  {
    archive.Write(reinterpret_cast<const unsigned char*>(inStr.data()),
                  inStr.size());
    archive.SetReadPosition(3, BinaryArchive::SeekDirection::END);

    std::string outStr(4, '\0');
    archive.Read(reinterpret_cast<unsigned char*>(outStr.data()), 3);

    ASSERT_STREQ(outStr.c_str(), "890");
  }

  archive.SetWritePosition(2, BinaryArchive::SeekDirection::END);

  {
    archive.Write(reinterpret_cast<const unsigned char*>(inStr.data()),
                  inStr.size());
    archive.SetReadPosition(3, BinaryArchive::SeekDirection::END);

    std::string outStr(4, '\0');
    archive.Read(reinterpret_cast<unsigned char*>(outStr.data()), 3);

    ASSERT_STREQ(outStr.c_str(), "890");
  }
}

TEST(BinaryArchiveTest,
     WriteTextSeekRead5BytesEndRead2BytesWrite11BytesSeek3EndRead3Bytes) {
  BinaryArchive archive;
  std::string inStr{"1234567890"};

  {
    archive.Write(reinterpret_cast<const unsigned char*>(inStr.data()),
                  inStr.size());
    archive.SetReadPosition(5, BinaryArchive::SeekDirection::END);

    std::string outStr(3, '\0');
    archive.Read(reinterpret_cast<unsigned char*>(outStr.data()), 2);

    ASSERT_STREQ(outStr.c_str(), "67");
  }

  {
    archive.Write(reinterpret_cast<const unsigned char*>(inStr.data()),
                  inStr.size());
    archive.SetReadPosition(3, BinaryArchive::SeekDirection::END);

    std::string outStr(4, '\0');
    archive.Read(reinterpret_cast<unsigned char*>(outStr.data()), 3);

    ASSERT_STREQ(outStr.c_str(), "890");
  }
}

TEST(BinaryArchiveTest, EmptyArchiveSeekReadDirOneByteFromBegin) {
  BinaryArchive archive;
  EXPECT_THROW(archive.SetReadPosition(1, BinaryArchive::SeekDirection::BEGIN),
               std::runtime_error);
}

TEST(BinaryArchiveTest, EmptyArchiveSeekReadDirMinusOneByteFromBegin) {
  BinaryArchive archive;
  EXPECT_THROW(archive.SetReadPosition(-1, BinaryArchive::SeekDirection::BEGIN),
               std::runtime_error);
}

TEST(BinaryArchiveTest, EmptyArchiveSeekReadDirOneByteFromEnd) {
  BinaryArchive archive;
  EXPECT_THROW(archive.SetReadPosition(1, BinaryArchive::SeekDirection::END),
               std::runtime_error);
}

TEST(BinaryArchiveTest, EmptyArchiveSeekReadDirMinusOneByteFromEnd) {
  BinaryArchive archive;
  EXPECT_THROW(archive.SetReadPosition(-1, BinaryArchive::SeekDirection::END),
               std::runtime_error);
}

TEST(BinaryArchiveTest, EmptyArchiveSeekReadDirOneByteFromRelative) {
  BinaryArchive archive;
  EXPECT_THROW(
      archive.SetReadPosition(1, BinaryArchive::SeekDirection::RELATIVE),
      std::runtime_error);
}

TEST(BinaryArchiveTest, EmptyArchiveSeekReadDirMinusOneByteFromRelative) {
  BinaryArchive archive;
  EXPECT_THROW(
      archive.SetReadPosition(-1, BinaryArchive::SeekDirection::RELATIVE),
      std::runtime_error);
}
