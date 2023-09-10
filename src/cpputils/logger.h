#pragma once
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

namespace CppUtils {
class Logger {
 public:
  Logger();

  template <typename... Args>
  static void Information(fmt::format_string<Args...> fmt, Args&&... args) {
    getInstance().console->info(fmt, std::forward<Args>(args)...);

    if (LOG_TO_FILE) {
      getInstance().file->info(fmt, std::forward<Args>(args)...);
      getInstance().file->flush();
    }
  }

  template <typename... Args>
  static void Warning(fmt::format_string<Args...> fmt, Args&&... args) {
    getInstance().console->warn(fmt, std::forward<Args>(args)...);

    if (LOG_TO_FILE) {
      getInstance().file->warn(fmt, std::forward<Args>(args)...);
      getInstance().file->flush();
    }
  }

  template <typename... Args>
  static void Error(fmt::format_string<Args...> fmt, Args&&... args) {
    getInstance().console->error(fmt, std::forward<Args>(args)...);

    if (LOG_TO_FILE) {
      getInstance().file->error(fmt, std::forward<Args>(args)...);
      getInstance().file->flush();
    }
  }

  template <typename... Args>
  static void Critical(fmt::format_string<Args...> fmt, Args&&... args) {
    getInstance().console->critical(fmt, std::forward<Args>(args)...);

    if (LOG_TO_FILE) {
      getInstance().file->critical(fmt, std::forward<Args>(args)...);
      getInstance().file->flush();
    }
  }

 private:
  static Logger& getInstance() {
    static Logger logger;
    return logger;
  }

 private:
  // Private const definitions.
  static const bool LOG_TO_FILE;
  static const char LOGFILE[];
  static const char LOGGER_CONSOLE[];
  static const char LOGGER_FILE[];

  std::shared_ptr<spdlog::logger> console;
  std::shared_ptr<spdlog::logger> file;
};
}  // namespace CppUtils
