/*
 * arrays_tests.cpp
 *
 *  Created on: 23 Jul 2021
 *      Author: ykhan
 */
#include "../src/arrays/arrays.h"
#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

using namespace std;

TEST(Arrays, FindMinMaxTest) {
	vector<int> arr{1, 2, 3, 4, 5};

	auto result = findMinMax(arr);
	pair<int, int> expected{1, 5};

	EXPECT_EQ(result, expected);
}

TEST(Arrays, RemoveTest) {
	vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 4};
	vec.erase(Remove(vec.begin(), vec.end(), 4), vec.end());

	vector<int> expected{1, 2, 3, 5, 6, 7, 8};

	EXPECT_EQ(expected, vec);
}


