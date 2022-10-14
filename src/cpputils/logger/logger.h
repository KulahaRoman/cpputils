#pragma once
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

class Logger {
 public:
  static void BeginBlock() { mx.lock(); }

  static void EndBlock() { mx.unlock(); }

  template <typename Arg, typename... Args>
  static void Information(Arg&& arg, Args&&... args) noexcept {
    auto lock = std::unique_lock<std::recursive_mutex>(mx);
    setConsoleColor(ConsoleColor::AQUA);
#if defined(UNICODE) || defined(_UNICODE)
    print(L"INFO", std::forward<Arg>(arg), std::forward<Args>(args)...);
#else
    print("INFO", std::forward<Arg>(arg), std::forward<Args>(args)...);
#endif
    setConsoleColor(ConsoleColor::RESET);
  }

  template <typename Arg, typename... Args>
  static void Warning(Arg&& arg, Args&&... args) noexcept {
    auto lock = std::unique_lock<std::recursive_mutex>(mx);
    setConsoleColor(ConsoleColor::YELLOW);
#if defined(UNICODE) || defined(_UNICODE)
    print(L"WARNING", std::forward<Arg>(arg), std::forward<Args>(args)...);
#else
    print("WARNING", std::forward<Arg>(arg), std::forward<Args>(args)...);
#endif
    setConsoleColor(ConsoleColor::RESET);
  }

  template <typename Arg, typename... Args>
  static void Error(Arg&& arg, Args&&... args) noexcept {
    auto lock = std::unique_lock<std::recursive_mutex>(mx);
    setConsoleColor(ConsoleColor::RED);
#if defined(UNICODE) || defined(_UNICODE)
    print(L"ERROR", std::forward<Arg>(arg), std::forward<Args>(args)...);
#else
    print("ERROR", std::forward<Arg>(arg), std::forward<Args>(args)...);
#endif
    setConsoleColor(ConsoleColor::RESET);
  }

  template <typename Arg, typename... Args>
  static void Critical(Arg&& arg, Args&&... args) noexcept {
    auto lock = std::unique_lock<std::recursive_mutex>(mx);
    setConsoleColor(ConsoleColor::PURPLE);
#if defined(UNICODE) || defined(_UNICODE)
    print(L"CRITICAL", std::forward<Arg>(arg), std::forward<Args>(args)...);
#else
    print("CRITICAL", std::forward<Arg>(arg), std::forward<Args>(args)...);
#endif
    setConsoleColor(ConsoleColor::RESET);
  }

 private:
  template <typename Arg, typename... Args>
#if defined(UNICODE) || defined(_UNICODE)
  static void print(const std::wstring& keyWord, Arg&& arg,
                    Args&&... args) noexcept {
    std::wcout << L"[THREAD " << std::this_thread::get_id() << L"]";
    std::wcout << L"[" << keyWord << L"]: ";
    std::wcout << std::forward<Arg>(arg);
    ((std::wcout << std::forward<Args>(args)), ...);
    std::wcout << std::endl;
  }
#else
  static void print(const std::string& keyWord, Arg&& arg,
                    Args&&... args) noexcept {
    std::cout << "[THREAD " << std::this_thread::get_id() << "]";
    std::cout << "[" << keyWord << "]: ";
    std::cout << std::forward<Arg>(arg);
    ((std::cout << std::forward<Args>(args)), ...);
    std::cout << std::endl;
  }
#endif

  static void setConsoleColor(ConsoleColor color) {
#ifdef __linux__
    std::cout << color;
#elif _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, static_cast<WORD>(color));
#endif
  }

 private:
  static std::recursive_mutex mx;
};
