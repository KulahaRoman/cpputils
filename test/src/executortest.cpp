#include <cpputils/threadpertaskexecutor.h>
#include <cpputils/threadpoolexecutor.h>
#include <gtest/gtest.h>

#include <chrono>
#include <thread>

using namespace CppUtils;
using namespace CppUtils::Execution;

TEST(ExecutorTest, ThreadPerTaskLaunch) {
  Logger::ToggleConsole(true);

  auto executor = std::make_shared<ThreadPerTaskExecutor>();

  for (int i = 0; i < 500; i++) {
    executor->Execute(
        [] { std::this_thread::sleep_for(std::chrono::seconds(1)); });
  }
}
