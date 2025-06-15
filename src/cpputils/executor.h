#pragma once
#include <functional>

namespace CppUtils {
namespace Execution {
using Task = std::function<void()>;

class Executor {
 public:
  virtual ~Executor() = default;

  virtual void Execute(const Task& task) = 0;
};
}  // namespace Execution
}  // namespace CppUtils
