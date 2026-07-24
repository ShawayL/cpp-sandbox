#ifndef SAMPLE_LIBRARY0_INTERNAL_ADD_HELPER_HPP
#define SAMPLE_LIBRARY0_INTERNAL_ADD_HELPER_HPP

// This header lives in the module-local "internal" directory.
// Unlike a "detail" header, it is reachable ONLY from within sample_library0
// itself, because the internal directory is added as a PRIVATE include path.
// Other modules (e.g. sample_library1) cannot include it.
//
// No SAMPLE_LIBRARY0_EXPORT is needed here: the symbol is only ever called from
// within the same shared library, so it never crosses a DLL boundary.
namespace sample_library0 {
namespace internal {

// Internal helper shared across sample_library0's own translation units.
int AddHelper(int a, int b) noexcept;

}  // namespace internal
}  // namespace sample_library0

#endif
