#include <cpputils/countdownlatch.h>
#include <cpputils/logger.h>
#include <gtest/gtest.h>

using namespace CppUtils;

TEST(LoggerTest, LogToConsole) {
  Logger::ToggleConsole(true);

  auto log = [] {
    Logger::Information("Information log.");
    Logger::Warning("Warning log.");
    Logger::Error("Error log.");
    Logger::Critical("Critical log.");
  };

  EXPECT_NO_THROW(log());
}

TEST(LoggerTest, LogNeitherConsoleNorFile) {
  Logger::ToggleConsole(false);
  Logger::ToggleFile(false);

  auto log = [] {
    Logger::Information("Information log.");
    Logger::Warning("Warning log.");
    Logger::Error("Error log.");
    Logger::Critical("Critical log.");
  };

  EXPECT_NO_THROW(log());
}

TEST(LoggerTest, NotLogToConsoleButToFile) {
  Logger::ToggleConsole(false);
  Logger::ToggleFile(true, "logs.txt");

  auto log = [] {
    Logger::Information("Information log.");
    Logger::Warning("Warning log.");
    Logger::Error("Error log.");
    Logger::Critical("Critical log.");
  };

  EXPECT_NO_THROW(log());
}

TEST(LoggerTest, LogToConsoleAndToFile) {
  Logger::ToggleConsole(true);
  Logger::ToggleFile(true, "logs.txt");

  auto log = [] {
    Logger::Information("Information log.");
    Logger::Warning("Warning log.");
    Logger::Error("Error log.");
    Logger::Critical("Critical log.");
  };

  EXPECT_NO_THROW(log());
}

TEST(LoggerTest, MultithreadedLogging) {
  Logger::ToggleConsole(false);
  Logger::ToggleFile(true, "logs.txt");

  auto latch = std::make_shared<Synchronization::CountDownLatch>(2);

  auto log0 = [latch] {
    for (int i = 0; i < 20; i++) {
      Logger::Information("Multithreaded info {}.", i);
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    latch->CountDown();
  };

  auto log1 = [latch] {
    for (int i = 0; i < 20; i++) {
      Logger::Information("Multithreaded info {}.", i);
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    latch->CountDown();
  };

  std::thread th0(log0);
  std::thread th1(log1);

  th0.detach();
  th1.detach();

  latch->Await();
}
