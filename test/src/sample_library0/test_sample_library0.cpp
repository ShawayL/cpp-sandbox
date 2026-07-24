#include <gtest/gtest.h>
#include <cpp_sandbox/sample_library0/sample_library0.hpp>

// ============================================================================
// Factorial
// ============================================================================

TEST(SampleLibrary0, FactorialZero) {
    EXPECT_EQ(sample_library0::Factorial(0), 1);
}

TEST(SampleLibrary0, FactorialOne) {
    EXPECT_EQ(sample_library0::Factorial(1), 1);
}

TEST(SampleLibrary0, FactorialTwo) {
    EXPECT_EQ(sample_library0::Factorial(2), 2);
}

TEST(SampleLibrary0, FactorialThree) {
    EXPECT_EQ(sample_library0::Factorial(3), 6);
}

TEST(SampleLibrary0, FactorialTen) {
    EXPECT_EQ(sample_library0::Factorial(10), 3628800);
}

// ============================================================================
// Sum
// ============================================================================

TEST(SampleLibrary0, SumPositive) {
    EXPECT_EQ(sample_library0::Sum(3, 5), 8);
}

TEST(SampleLibrary0, SumNegative) {
    EXPECT_EQ(sample_library0::Sum(-3, -5), -8);
}

TEST(SampleLibrary0, SumMixedSigns) {
    EXPECT_EQ(sample_library0::Sum(10, -3), 7);
}

TEST(SampleLibrary0, SumWithZero) {
    EXPECT_EQ(sample_library0::Sum(0, 5), 5);
    EXPECT_EQ(sample_library0::Sum(5, 0), 5);
    EXPECT_EQ(sample_library0::Sum(0, 0), 0);
}

// ============================================================================
// FactorialConstexpr
// ============================================================================

TEST(SampleLibrary0, FactorialConstexprZero) {
    constexpr int kResult = sample_library0::FactorialConstexpr(0);
    EXPECT_EQ(kResult, 1);
}

TEST(SampleLibrary0, FactorialConstexprOne) {
    constexpr int kResult = sample_library0::FactorialConstexpr(1);
    EXPECT_EQ(kResult, 1);
}

TEST(SampleLibrary0, FactorialConstexprTwo) {
    constexpr int kResult = sample_library0::FactorialConstexpr(2);
    EXPECT_EQ(kResult, 2);
}

TEST(SampleLibrary0, FactorialConstexprThree) {
    constexpr int kResult = sample_library0::FactorialConstexpr(3);
    EXPECT_EQ(kResult, 6);
}

TEST(SampleLibrary0, FactorialConstexprTen) {
    constexpr int kResult = sample_library0::FactorialConstexpr(10);
    EXPECT_EQ(kResult, 3628800);
}
