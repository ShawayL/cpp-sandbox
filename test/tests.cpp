#include <catch2/catch_test_macros.hpp>
#include <cpp_sandbox/sample_library0.hpp>
#include <cpp_sandbox/sample_library1.hpp>

TEST_CASE("Factorials are computed", "[factorial]") {
  REQUIRE(sample_library0::factorial(0) == 1);
  REQUIRE(sample_library0::factorial(1) == 1);
  REQUIRE(sample_library0::factorial(2) == 2);
  REQUIRE(sample_library0::factorial(3) == 6);
  REQUIRE(sample_library0::factorial(10) == 3628800);

  REQUIRE(sample_library1::factorial(0) == 1);
  REQUIRE(sample_library1::factorial(1) == 1);
  REQUIRE(sample_library1::factorial(2) == 2);
  REQUIRE(sample_library1::factorial(3) == 6);
  REQUIRE(sample_library1::factorial(10) == 3628800);
}
