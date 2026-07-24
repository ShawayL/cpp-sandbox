#ifndef SAMPLE_LIBRARY1_HPP
#define SAMPLE_LIBRARY1_HPP

#include <cpp_sandbox/sample_library1/sample_library1_export.hpp>

namespace sample_library1 {

SAMPLE_LIBRARY1_EXPORT int Factorial(int) noexcept;

SAMPLE_LIBRARY1_EXPORT int FactorialNoexp(int) noexcept;

// Demonstrates calling sample_library0's internal detail header: returns a * b.
SAMPLE_LIBRARY1_EXPORT int Multiply(int a, int b) noexcept;

constexpr int FactorialConstexpr(int input) noexcept {
  if (input == 0) {
    return 1;
  }

  return input * FactorialConstexpr(input - 1);
}

}  // namespace sample_library1

#endif
