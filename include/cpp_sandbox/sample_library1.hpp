#ifndef SAMPLE_LIBRARY1_HPP
#define SAMPLE_LIBRARY1_HPP

#include <cpp_sandbox/sample_library1_export.hpp>

namespace sample_library1 {

SAMPLE_LIBRARY1_EXPORT int factorial(int) noexcept;

int factorial_noexp(int) noexcept;

constexpr int factorial_constexpr(int input) noexcept {
  if (input == 0) {
    return 1;
  }

  return input * factorial_constexpr(input - 1);
}

}  // namespace sample_library1

#endif
