#include "logger.h"

Logger::Logger()
    : console(spdlog::stdout_color_mt(LOGGER_CONSOLE)),
      file(spdlog::basic_logger_mt(LOGGER_FILE, LOGFILE)) {
  spdlog::get(LOGGER_CONSOLE)
      ->set_pattern("[%H:%M:%S %z][TH %t][%^---%L---%$]: %v");
  spdlog::get(LOGGER_FILE)
      ->set_pattern("[%H:%M:%S %z][TH %t][%^---%L---%$]: %v");
}
