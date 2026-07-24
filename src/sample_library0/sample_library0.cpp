#include <cpp_sandbox/sample_library0/sample_library0.hpp>

// Module-local internal header, included by file name via the PRIVATE include path.
#include <add_helper.hpp>

#ifdef SAMPLE_LIBRARY0_STATIC_DEFINE
int static_library0 = 0;
#endif

int sample_library0::Factorial(int input) noexcept
{
  int result = 1;

  while (input > 0) {
    result *= input;
    --input;
  }

  return result;
}

int sample_library0::Sum(int a, int b) noexcept {
  return sample_library0::internal::AddHelper(a, b);
}
