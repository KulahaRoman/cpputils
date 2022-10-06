#pragma once
#include <iostream>
#include <mutex>

class Logger {
 public:
  static void BeginLoggingBlock() { mx.lock(); }

  static void EndLoggingBlock() { mx.unlock(); }

  template <typename Arg, typename... Args>
  static void Information(Arg&& arg, Args&&... args) noexcept {
    auto lock = std::unique_lock<std::recursive_mutex>(mx);
    std::wcout << "[THREAD " << std::this_thread::get_id() << "]";
    std::wcout << "[INFO]: ";
    std::wcout << std::forward<Arg>(arg);
    ((std::wcout << std::forward<Args>(args)), ...);
    std::wcout << std::endl;
  }

  template <typename Arg, typename... Args>
  static void Warning(Arg&& arg, Args&&... args) noexcept {
    auto lock = std::unique_lock<std::recursive_mutex>(mx);
    std::wcout << "[THREAD " << std::this_thread::get_id() << "]";
    std::wcout << "[WARNING]: ";
    std::wcout << std::forward<Arg>(arg);
    ((std::wcout << std::forward<Args>(args)), ...);
    std::wcout << std::endl;
  }

  template <typename Arg, typename... Args>
  static void Error(Arg&& arg, Args&&... args) noexcept {
    auto lock = std::unique_lock<std::recursive_mutex>(mx);
    std::wcout << "[THREAD " << std::this_thread::get_id() << "]";
    std::wcout << "[ERROR]: ";
    std::wcout << std::forward<Arg>(arg);
    ((std::wcout << std::forward<Args>(args)), ...);
    std::wcout << std::endl;
  }

  template <typename Arg, typename... Args>
  static void Critical(Arg&& arg, Args&&... args) noexcept {
    auto lock = std::unique_lock<std::recursive_mutex>(mx);
    std::wcout << "[THREAD " << std::this_thread::get_id() << "]";
    std::wcout << "[CRITICAL]: ";
    std::wcout << std::forward<Arg>(arg);
    ((std::wcout << std::forward<Args>(args)), ...);
    std::wcout << std::endl;
  }

 private:
  static std::recursive_mutex mx;
};
