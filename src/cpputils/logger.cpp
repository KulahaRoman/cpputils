#include "logger.h"

namespace CppUtils {
const bool Logger::LOG_TO_FILE = true;
const char Logger::LOGFILE[] = "logs.txt";
const char Logger::LOGGER_CONSOLE[] = "console";
const char Logger::LOGGER_FILE[] = "file";

Logger::Logger()
    : console(spdlog::stdout_color_mt(LOGGER_CONSOLE)),
      file(spdlog::basic_logger_mt(LOGGER_FILE, LOGFILE)) {
  spdlog::get(LOGGER_CONSOLE)
      ->set_pattern("[%H:%M:%S %z][TH %t][%^---%L---%$]: %v");
  spdlog::get(LOGGER_FILE)
      ->set_pattern("[%H:%M:%S %z][TH %t][%^---%L---%$]: %v");
}
}  // namespace CppUtils
