#ifndef SAMPLE_LIBRARY0_HPP
#define SAMPLE_LIBRARY0_HPP

#include <cpp_sandbox/sample_library0/sample_library0_export.hpp>

namespace sample_library0 {

SAMPLE_LIBRARY0_EXPORT int Factorial(int) noexcept;

// Public API that internally delegates to the module-local internal helper.
SAMPLE_LIBRARY0_EXPORT int Sum(int a, int b) noexcept;

constexpr int FactorialConstexpr(int input) noexcept {
  if (input == 0) {
    return 1;
  }

  return input * FactorialConstexpr(input - 1);
}

}  // namespace sample_library0

#endif
