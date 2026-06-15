#include <gtest/gtest.h>
#include <cpp_sandbox/sample_library1/sample_library1.hpp>

// ============================================================================
// factorial
// ============================================================================

TEST(SampleLibrary1Test, factorial_zero) {
    EXPECT_EQ(sample_library1::factorial(0), 1);
}

TEST(SampleLibrary1Test, factorial_one) {
    EXPECT_EQ(sample_library1::factorial(1), 1);
}

TEST(SampleLibrary1Test, factorial_two) {
    EXPECT_EQ(sample_library1::factorial(2), 2);
}

TEST(SampleLibrary1Test, factorial_three) {
    EXPECT_EQ(sample_library1::factorial(3), 6);
}

TEST(SampleLibrary1Test, factorial_ten) {
    EXPECT_EQ(sample_library1::factorial(10), 3628800);
}

// ============================================================================
// factorial_noexp
// ============================================================================

TEST(SampleLibrary1Test, factorial_noexp_zero) {
    EXPECT_EQ(sample_library1::factorial_noexp(0), 1);
}

TEST(SampleLibrary1Test, factorial_noexp_one) {
    EXPECT_EQ(sample_library1::factorial_noexp(1), 1);
}

TEST(SampleLibrary1Test, factorial_noexp_two) {
    EXPECT_EQ(sample_library1::factorial_noexp(2), 2);
}

TEST(SampleLibrary1Test, factorial_noexp_three) {
    EXPECT_EQ(sample_library1::factorial_noexp(3), 6);
}

TEST(SampleLibrary1Test, factorial_noexp_ten) {
    EXPECT_EQ(sample_library1::factorial_noexp(10), 3628800);
}

// ============================================================================
// multiply
// ============================================================================

TEST(SampleLibrary1Test, multiply_positive) {
    EXPECT_EQ(sample_library1::multiply(3, 5), 15);
}

TEST(SampleLibrary1Test, multiply_negative_single) {
    EXPECT_EQ(sample_library1::multiply(-3, 5), -15);
}

TEST(SampleLibrary1Test, multiply_negative_both) {
    EXPECT_EQ(sample_library1::multiply(-3, -5), 15);
}

TEST(SampleLibrary1Test, multiply_with_zero) {
    EXPECT_EQ(sample_library1::multiply(0, 5), 0);
    EXPECT_EQ(sample_library1::multiply(5, 0), 0);
    EXPECT_EQ(sample_library1::multiply(0, 0), 0);
}

TEST(SampleLibrary1Test, multiply_with_one) {
    EXPECT_EQ(sample_library1::multiply(1, 7), 7);
    EXPECT_EQ(sample_library1::multiply(7, 1), 7);
}

// ============================================================================
// factorial_constexpr
// ============================================================================

TEST(SampleLibrary1Test, factorial_constexpr_zero) {
    constexpr int result = sample_library1::factorial_constexpr(0);
    EXPECT_EQ(result, 1);
}

TEST(SampleLibrary1Test, factorial_constexpr_one) {
    constexpr int result = sample_library1::factorial_constexpr(1);
    EXPECT_EQ(result, 1);
}

TEST(SampleLibrary1Test, factorial_constexpr_two) {
    constexpr int result = sample_library1::factorial_constexpr(2);
    EXPECT_EQ(result, 2);
}

TEST(SampleLibrary1Test, factorial_constexpr_three) {
    constexpr int result = sample_library1::factorial_constexpr(3);
    EXPECT_EQ(result, 6);
}

TEST(SampleLibrary1Test, factorial_constexpr_ten) {
    constexpr int result = sample_library1::factorial_constexpr(10);
    EXPECT_EQ(result, 3628800);
}
