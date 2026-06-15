// Included by file name only, which works because sample_library0 adds its
// internal/ directory as a PRIVATE include path.
#include <add_helper.hpp>

int sample_library0::internal::add(int a, int b) noexcept {
  return a + b;
}
