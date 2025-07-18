#include <cpp_sandbox/sample_library0.hpp>
#include <cpp_sandbox/sample_library1.hpp>
#include <iostream>

int main() {
  std::cout << "sample_library0::factorial(5) = "
            << sample_library0::factorial(5) << std::endl;

  std::cout << "sample_library1::factorial(6) = "
            << sample_library1::factorial(6) << std::endl;

  //std::cout << "sample_library1::factorial_noexp(6) = "
  //          << sample_library1::factorial_noexp(6) << std::endl;

  return 0;
}