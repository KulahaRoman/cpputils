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
    #if defined(UNICODE) || defined(_UNICODE)
      print(L"INFO", std::forward<Arg>(arg), std::forward<Args>(args)...);
    #else
      print("INFO", std::forward<Arg>(arg), std::forward<Args>(args)...);
    #endif
  }

  template <typename Arg, typename... Args>
  static void Warning(Arg&& arg, Args&&... args) noexcept {
    auto lock = std::unique_lock<std::recursive_mutex>(mx);
    #if defined(UNICODE) || defined(_UNICODE)
      print(L"WARNING", std::forward<Arg>(arg), std::forward<Args>(args)...);
    #else
      print("WARNING", std::forward<Arg>(arg), std::forward<Args>(args)...);
    #endif
  }

  template <typename Arg, typename... Args>
  static void Error(Arg&& arg, Args&&... args) noexcept {
    auto lock = std::unique_lock<std::recursive_mutex>(mx);
    #if defined(UNICODE) || defined(_UNICODE)
      print(L"ERROR", std::forward<Arg>(arg), std::forward<Args>(args)...);
    #else
      print("ERROR", std::forward<Arg>(arg), std::forward<Args>(args)...);
    #endif
  }

  template <typename Arg, typename... Args>
  static void Critical(Arg&& arg, Args&&... args) noexcept {
    auto lock = std::unique_lock<std::recursive_mutex>(mx);
    #if defined(UNICODE) || defined(_UNICODE)
      print(L"CRITICAL", std::forward<Arg>(arg), std::forward<Args>(args)...);
    #else
      print("CRITICAL", std::forward<Arg>(arg), std::forward<Args>(args)...);
    #endif
  }

 private:
  template <typename Arg, typename... Args>
#if defined(UNICODE) || defined(_UNICODE)
    static void print(const std::wstring& keyWord, Arg&& arg, Args&&... args) noexcept {
    std::wcout << L"[THREAD " << std::this_thread::get_id() << L"]";
    std::wcout << L"[" << keyWord << L"]: ";
    std::wcout << std::forward<Arg>(arg);
    ((std::wcout << std::forward<Args>(args)), ...);
    std::wcout << std::endl;  
  }
#else
static void print(const std::string& keyWord, Arg&& arg, Args&&... args) noexcept {
    std::cout << "[THREAD " << std::this_thread::get_id() << "]";
    std::cout << "[" << keyWord << "]: ";
    std::cout << std::forward<Arg>(arg);
    ((std::cout << std::forward<Args>(args)), ...);
    std::cout << std::endl;
  }
#endif
 private:
  static std::recursive_mutex mx;
};
