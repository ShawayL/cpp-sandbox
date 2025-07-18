#ifndef SAMPLE_LIBRARY0_HPP
#define SAMPLE_LIBRARY0_HPP

#include <cpp_sandbox/sample_library0_export.hpp>

namespace sample_library0 {

SAMPLE_LIBRARY0_EXPORT int factorial(int) noexcept;

constexpr int factorial_constexpr(int input) noexcept {
  if (input == 0) {
    return 1;
  }

  return input * factorial_constexpr(input - 1);
}

}  // namespace sample_library0

#endif
