#include <cpp_sandbox/sample_library0.hpp>

#ifdef SAMPLE_LIBRARY0_STATIC_DEFINE
int static_library0 = 0;
#endif

int sample_library0::factorial(int input) noexcept
{
  int result = 1;

  while (input > 0) {
    result *= input;
    --input;
  }

  return result;
}
