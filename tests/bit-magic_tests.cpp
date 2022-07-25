/*
 * bit-magic_tests.cpp
 *
 *  Created on: 6 Sep 2021
 *      Author: ykhan
 */

#include "../src/bit-magic/bit-magic.h"
#include <gtest/gtest.h>

TEST(BitMagic, CountLongestSequenceZeroesTest) {
	EXPECT_EQ(0, countLongestSequenceZeroes(15));
	EXPECT_EQ(3, countLongestSequenceZeroes(561892));
	EXPECT_EQ(5, countLongestSequenceZeroes(1041));
}


