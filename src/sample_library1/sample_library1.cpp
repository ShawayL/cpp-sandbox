#include <cpp_sandbox/sample_library0/sample_library0.hpp>
// Include sample_library0's internal detail header.
// It is not installed, but is reachable from modules inside this project via
// sample_library0's build-time PUBLIC include directory.
#include <cpp_sandbox/sample_library0/detail/multiply_helper.hpp>
#include <cpp_sandbox/sample_library1/sample_library1.hpp>

#ifdef SAMPLE_LIBRARY1_STATIC_DEFINE
int static_library1 = 0;
#endif

int sample_library1::Factorial(int input) noexcept {
  return sample_library0::Factorial(input);
}

int sample_library1::FactorialNoexp(int input) noexcept {
  return sample_library1::Factorial(input);
}

int sample_library1::Multiply(int a, int b) noexcept {
  return sample_library0::detail::MultiplyHelper(a, b);
}
