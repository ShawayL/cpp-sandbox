#include <cpp_sandbox/sample_library0/sample_library0.hpp>
#include <cpp_sandbox/sample_library1/sample_library1.hpp>
#include <iostream>

int main() {
  std::cout << "sample_library0::Factorial(5) = "
            << sample_library0::Factorial(5) << std::endl;

  std::cout << "sample_library1::Factorial(6) = "
            << sample_library1::Factorial(6) << std::endl;

  //std::cout << "sample_library1::FactorialNoexp(6) = "
  //          << sample_library1::FactorialNoexp(6) << std::endl;

  return 0;
}