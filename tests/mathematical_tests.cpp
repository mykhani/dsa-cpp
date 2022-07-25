/*
 * mathematical_tests.cpp
 *
 *  Created on: 16 Jul 2021
 *      Author: ykhan
 */
#include "../src/mathematical/mathematical.h"
#include <gtest/gtest.h>

TEST(Mathematical, CountDigitsTest) {
	EXPECT_EQ(4, count_digits(9235));
	EXPECT_EQ(4, count_digits(-9235));
}

TEST(Mathematical, PalindromeTest) {
	EXPECT_EQ(true, is_palindrome(78987));
	EXPECT_EQ(false, is_palindrome(123));
}

TEST(Mathematical, FactorialTest) {
	EXPECT_EQ(1, factorial(0));
	EXPECT_EQ(3628800, factorial(10));
}

TEST(Mathematical, TrailingZeroesFactorialTest) {
	EXPECT_EQ(0, trailing_zeroes_in_factorial(1));
	EXPECT_EQ(0, trailing_zeroes_in_factorial(0));
	EXPECT_EQ(1, trailing_zeroes_in_factorial(5));
	EXPECT_EQ(24, trailing_zeroes_in_factorial(100));
}
