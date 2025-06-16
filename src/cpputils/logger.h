#pragma once
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#include <algorithm>
#include <mutex>

namespace CppUtils {
class Logger {
 public:
  Logger();

  static void ToggleConsole(bool enabled) {
    auto& inst = getInstance();
    auto lock = std::unique_lock<std::mutex>(inst.mx);

    inst.consoleLogging = enabled;

    if (inst.console) {
      spdlog::drop(LOGGER_CONSOLE);
    }

    if (enabled) {
      inst.console = spdlog::stdout_color_mt(LOGGER_CONSOLE);
      inst.console->set_pattern("[%H:%M:%S %z][TH %t][%^---%L---%$]: %v");
    }
  }

  static void ToggleFile(bool enabled, const std::string& fileName = {}) {
    auto& inst = getInstance();
    auto lock = std::unique_lock<std::mutex>(inst.mx);

    inst.fileLogging = enabled;

    if (inst.file) {
      spdlog::drop(LOGGER_FILE);
    }

    if (enabled) {
      inst.file = spdlog::basic_logger_mt(LOGGER_FILE, fileName);
      inst.file->set_pattern("[%H:%M:%S %z][TH %t][%^---%L---%$]: %v");
    }
  }

  static void SetLevel(const std::string& level);

  template <typename... Args>
  static void Information(fmt::format_string<Args...> fmt, Args&&... args) {
    auto& inst = getInstance();
    auto lock = std::unique_lock<std::mutex>(inst.mx);

    if (inst.consoleLogging) {
      inst.console->info(fmt, std::forward<Args>(args)...);
      inst.console->flush();
    }

    if (inst.fileLogging) {
      inst.file->info(fmt, std::forward<Args>(args)...);
      inst.file->flush();
    }
  }

  template <typename... Args>
  static void Debug(fmt::format_string<Args...> fmt, Args&&... args) {
    auto& inst = getInstance();
    auto lock = std::unique_lock<std::mutex>(inst.mx);

    if (inst.consoleLogging) {
      inst.console->debug(fmt, std::forward<Args>(args)...);
      inst.console->flush();
    }

    if (inst.fileLogging) {
      inst.file->debug(fmt, std::forward<Args>(args)...);
      inst.file->flush();
    }
  }

  template <typename... Args>
  static void Warning(fmt::format_string<Args...> fmt, Args&&... args) {
    auto& inst = getInstance();
    auto lock = std::unique_lock<std::mutex>(inst.mx);

    if (inst.consoleLogging) {
      inst.console->warn(fmt, std::forward<Args>(args)...);
      inst.console->flush();
    }

    if (inst.fileLogging) {
      inst.file->warn(fmt, std::forward<Args>(args)...);
      inst.file->flush();
    }
  }

  template <typename... Args>
  static void Error(fmt::format_string<Args...> fmt, Args&&... args) {
    auto& inst = getInstance();
    auto lock = std::unique_lock<std::mutex>(inst.mx);

    if (inst.consoleLogging) {
      inst.console->error(fmt, std::forward<Args>(args)...);
      inst.console->flush();
    }

    if (inst.fileLogging) {
      inst.file->error(fmt, std::forward<Args>(args)...);
      inst.file->flush();
    }
  }

  template <typename... Args>
  static void Critical(fmt::format_string<Args...> fmt, Args&&... args) {
    auto& inst = getInstance();
    auto lock = std::unique_lock<std::mutex>(inst.mx);

    if (inst.consoleLogging) {
      inst.console->critical(fmt, std::forward<Args>(args)...);
      inst.console->flush();
    }

    if (inst.fileLogging) {
      inst.file->critical(fmt, std::forward<Args>(args)...);
      inst.file->flush();
    }
  }

 private:
  static Logger& getInstance() {
    static Logger logger;
    return logger;
  }

 private:
  static const char LOGGER_CONSOLE[];
  static const char LOGGER_FILE[];

  std::mutex mx;

  bool consoleLogging;
  bool fileLogging;

  std::shared_ptr<spdlog::logger> console;
  std::shared_ptr<spdlog::logger> file;
};
}  // namespace CppUtils
