#include "logger.h"

Logger::Logger() { fout.open("logs.txt", std::ios::out | std::ios::app); }

Logger::~Logger() {
  if (fout.is_open()) {
    fout.close();
  }
}
