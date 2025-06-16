#include "logger.h"

namespace CppUtils {
const char Logger::LOGGER_CONSOLE[] = "console";
const char Logger::LOGGER_FILE[] = "file";

Logger::Logger() : consoleLogging(false), fileLogging(false) {}

void Logger::SetLevel(const std::string& level) {
  std::string lower(level);
  std::transform(level.begin(), level.end(), lower.begin(),
                 [](unsigned char c) { return std::tolower(c); });

  if (lower == "info") {
    spdlog::set_level(spdlog::level::info);
  } else if (lower == "debug") {
    spdlog::set_level(spdlog::level::debug);
  } else if (lower == "warn") {
    spdlog::set_level(spdlog::level::warn);
  } else if (lower == "error") {
    spdlog::set_level(spdlog::level::err);
  } else if (lower == "critical") {
    spdlog::set_level(spdlog::level::critical);
  } else {
    throw std::runtime_error("invalid logging level");
  }
}
}  // namespace CppUtils
