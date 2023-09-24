#include "logger.h"

namespace CppUtils {
const char Logger::LOGGER_CONSOLE[] = "console";
const char Logger::LOGGER_FILE[] = "file";

Logger::Logger() : consoleLogging(false), fileLogging(false) {}
}  // namespace CppUtils
