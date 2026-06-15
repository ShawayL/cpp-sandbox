#include <gtest/gtest.h>
#include <cpp_sandbox/sample_library0/sample_library0.hpp>

// ============================================================================
// factorial
// ============================================================================

TEST(sample_library0, factorial_zero) {
    EXPECT_EQ(sample_library0::factorial(0), 1);
}

TEST(sample_library0, factorial_one) {
    EXPECT_EQ(sample_library0::factorial(1), 1);
}

TEST(sample_library0, factorial_two) {
    EXPECT_EQ(sample_library0::factorial(2), 2);
}

TEST(sample_library0, factorial_three) {
    EXPECT_EQ(sample_library0::factorial(3), 6);
}

TEST(sample_library0, factorial_ten) {
    EXPECT_EQ(sample_library0::factorial(10), 3628800);
}

// ============================================================================
// sum
// ============================================================================

TEST(sample_library0, sum_positive) {
    EXPECT_EQ(sample_library0::sum(3, 5), 8);
}

TEST(sample_library0, sum_negative) {
    EXPECT_EQ(sample_library0::sum(-3, -5), -8);
}

TEST(sample_library0, sum_mixed_signs) {
    EXPECT_EQ(sample_library0::sum(10, -3), 7);
}

TEST(sample_library0, sum_with_zero) {
    EXPECT_EQ(sample_library0::sum(0, 5), 5);
    EXPECT_EQ(sample_library0::sum(5, 0), 5);
    EXPECT_EQ(sample_library0::sum(0, 0), 0);
}

// ============================================================================
// factorial_constexpr
// ============================================================================

TEST(sample_library0, factorial_constexpr_zero) {
    constexpr int result = sample_library0::factorial_constexpr(0);
    EXPECT_EQ(result, 1);
}

TEST(sample_library0, factorial_constexpr_one) {
    constexpr int result = sample_library0::factorial_constexpr(1);
    EXPECT_EQ(result, 1);
}

TEST(sample_library0, factorial_constexpr_two) {
    constexpr int result = sample_library0::factorial_constexpr(2);
    EXPECT_EQ(result, 2);
}

TEST(sample_library0, factorial_constexpr_three) {
    constexpr int result = sample_library0::factorial_constexpr(3);
    EXPECT_EQ(result, 6);
}

TEST(sample_library0, factorial_constexpr_ten) {
    constexpr int result = sample_library0::factorial_constexpr(10);
    EXPECT_EQ(result, 3628800);
}
