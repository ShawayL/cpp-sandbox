#include <gtest/gtest.h>
#include <cpp_sandbox/sample_library1/sample_library1.hpp>

// ============================================================================
// Factorial
// ============================================================================

TEST(SampleLibrary1, FactorialZero) {
    EXPECT_EQ(sample_library1::Factorial(0), 1);
}

TEST(SampleLibrary1, FactorialOne) {
    EXPECT_EQ(sample_library1::Factorial(1), 1);
}

TEST(SampleLibrary1, FactorialTwo) {
    EXPECT_EQ(sample_library1::Factorial(2), 2);
}

TEST(SampleLibrary1, FactorialThree) {
    EXPECT_EQ(sample_library1::Factorial(3), 6);
}

TEST(SampleLibrary1, FactorialTen) {
    EXPECT_EQ(sample_library1::Factorial(10), 3628800);
}

// ============================================================================
// FactorialNoexp
// ============================================================================

TEST(SampleLibrary1, FactorialNoexpZero) {
    EXPECT_EQ(sample_library1::FactorialNoexp(0), 1);
}

TEST(SampleLibrary1, FactorialNoexpOne) {
    EXPECT_EQ(sample_library1::FactorialNoexp(1), 1);
}

TEST(SampleLibrary1, FactorialNoexpTwo) {
    EXPECT_EQ(sample_library1::FactorialNoexp(2), 2);
}

TEST(SampleLibrary1, FactorialNoexpThree) {
    EXPECT_EQ(sample_library1::FactorialNoexp(3), 6);
}

TEST(SampleLibrary1, FactorialNoexpTen) {
    EXPECT_EQ(sample_library1::FactorialNoexp(10), 3628800);
}

// ============================================================================
// Multiply
// ============================================================================

TEST(SampleLibrary1, MultiplyPositive) {
    EXPECT_EQ(sample_library1::Multiply(3, 5), 15);
}

TEST(SampleLibrary1, MultiplyNegativeSingle) {
    EXPECT_EQ(sample_library1::Multiply(-3, 5), -15);
}

TEST(SampleLibrary1, MultiplyNegativeBoth) {
    EXPECT_EQ(sample_library1::Multiply(-3, -5), 15);
}

TEST(SampleLibrary1, MultiplyWithZero) {
    EXPECT_EQ(sample_library1::Multiply(0, 5), 0);
    EXPECT_EQ(sample_library1::Multiply(5, 0), 0);
    EXPECT_EQ(sample_library1::Multiply(0, 0), 0);
}

TEST(SampleLibrary1, MultiplyWithOne) {
    EXPECT_EQ(sample_library1::Multiply(1, 7), 7);
    EXPECT_EQ(sample_library1::Multiply(7, 1), 7);
}

// ============================================================================
// FactorialConstexpr
// ============================================================================

TEST(SampleLibrary1, FactorialConstexprZero) {
    constexpr int kResult = sample_library1::FactorialConstexpr(0);
    EXPECT_EQ(kResult, 1);
}

TEST(SampleLibrary1, FactorialConstexprOne) {
    constexpr int kResult = sample_library1::FactorialConstexpr(1);
    EXPECT_EQ(kResult, 1);
}

TEST(SampleLibrary1, FactorialConstexprTwo) {
    constexpr int kResult = sample_library1::FactorialConstexpr(2);
    EXPECT_EQ(kResult, 2);
}

TEST(SampleLibrary1, FactorialConstexprThree) {
    constexpr int kResult = sample_library1::FactorialConstexpr(3);
    EXPECT_EQ(kResult, 6);
}

TEST(SampleLibrary1, FactorialConstexprTen) {
    constexpr int kResult = sample_library1::FactorialConstexpr(10);
    EXPECT_EQ(kResult, 3628800);
}
