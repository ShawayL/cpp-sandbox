#include <cpp_sandbox/sample_library0.hpp>
#include <cpp_sandbox/sample_library1.hpp>

#ifdef sample_library1_STATIC_DEFINE
int static_library1 = 0;
#endif

int sample_library1::factorial(int input) noexcept {
  return sample_library0::factorial(input);
}

int sample_library1::factorial_noexp(int input) noexcept {
  return sample_library1::factorial(input);
}
