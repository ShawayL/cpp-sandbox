#ifndef SAMPLE_LIBRARY0_DETAIL_MULTIPLY_HELPER_HPP
#define SAMPLE_LIBRARY0_DETAIL_MULTIPLY_HELPER_HPP

#include <cpp_sandbox/sample_library0/sample_library0_export.hpp>

// This header lives in the detail directory: it is an internal implementation
// detail of sample_library0. It may be included by any module inside this
// project (cpp_sandbox), but it is NOT installed / exported to downstream users.
namespace sample_library0 {
namespace detail {

// Internal helper: returns a * b.
// Exported with SAMPLE_LIBRARY0_EXPORT because the default build is a shared
// library and this symbol is called across the module (DLL) boundary.
SAMPLE_LIBRARY0_EXPORT int multiply(int a, int b) noexcept;

}  // namespace detail
}  // namespace sample_library0

#endif
