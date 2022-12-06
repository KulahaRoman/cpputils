#pragma once
#include <fstream>
#include <iostream>
#include <mutex>

#ifdef __linux__
enum class ConsoleColor {
  RESET = "\\033[39m",
  RED = "\\033[31m",
  GREEN = "\\033[32m",
  BLUE = "\\033[34m",
  AQUA = "\\033[36m",
  YELLOW = "\\033[33m",
  PURPLE = "\\033[35m"
};
#elif _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

enum class ConsoleColor : uint16_t {
  RESET = 0x07,
  RED = 0x04,
  GREEN = 0x02,
  BLUE = 0x01,
  AQUA = 0x03,
  YELLOW = 0x06,
  PURPLE = 0x05
};
#endif

#define LOGFILE

class Logger {
 public:
  Logger();
  ~Logger();

  static void BeginBlock() { getInstance().mx.lock(); }

  static void EndBlock() { getInstance().mx.unlock(); }

  template <typename Arg, typename... Args>
  static void Information(Arg&& arg, Args&&... args) noexcept {
    auto lock = std::unique_lock<std::recursive_mutex>(getInstance().mx);
    setConsoleColor(ConsoleColor::AQUA);
    getInstance().print("INFO", std::forward<Arg>(arg),
                        std::forward<Args>(args)...);
    setConsoleColor(ConsoleColor::RESET);
  }

  template <typename Arg, typename... Args>
  static void Warning(Arg&& arg, Args&&... args) noexcept {
    auto lock = std::unique_lock<std::recursive_mutex>(getInstance().mx);
    setConsoleColor(ConsoleColor::YELLOW);
    getInstance().print("WARNING", std::forward<Arg>(arg),
                        std::forward<Args>(args)...);
    setConsoleColor(ConsoleColor::RESET);
  }

  template <typename Arg, typename... Args>
  static void Error(Arg&& arg, Args&&... args) noexcept {
    auto lock = std::unique_lock<std::recursive_mutex>(getInstance().mx);
    setConsoleColor(ConsoleColor::RED);
    getInstance().print("ERROR", std::forward<Arg>(arg),
                        std::forward<Args>(args)...);
    setConsoleColor(ConsoleColor::RESET);
  }

  template <typename Arg, typename... Args>
  static void Critical(Arg&& arg, Args&&... args) noexcept {
    auto lock = std::unique_lock<std::recursive_mutex>(getInstance().mx);
    setConsoleColor(ConsoleColor::PURPLE);
    getInstance().print("CRITICAL", std::forward<Arg>(arg),
                        std::forward<Args>(args)...);
    setConsoleColor(ConsoleColor::RESET);
  }

 private:
  static Logger& getInstance() {
    static Logger logger;
    return logger;
  }

  template <typename Arg, typename... Args>
  void print(const std::string& keyWord, Arg&& arg, Args&&... args) noexcept {
#ifdef LOGFILE
    fout << "[THREAD " << std::this_thread::get_id() << "]";
    fout << "[" << keyWord << "]: ";
    fout << std::forward<Arg>(arg);
    ((fout << std::forward<Args>(args)), ...);
    fout << std::endl;
#endif

    std::cout << "[THREAD " << std::this_thread::get_id() << "]";
    std::cout << "[" << keyWord << "]: ";
    std::cout << std::forward<Arg>(arg);
    ((std::cout << std::forward<Args>(args)), ...);
    std::cout << std::endl;
  }

  static void setConsoleColor(ConsoleColor color) {
#ifdef __linux__
    std::cout << color;
#elif _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, static_cast<WORD>(color));
#endif
  }

 private:
  std::ofstream fout;
  std::recursive_mutex mx;
};
