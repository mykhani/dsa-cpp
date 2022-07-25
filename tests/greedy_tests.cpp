/*
 * greedy_tests.cpp
 *
 *  Created on: 16 Jul 2021
 *      Author: ykhan
 */

#include "../src/greedy/greedy.h"
#include <gtest/gtest.h>

TEST(Greedy, MinimumCoinsTest) {
	std::vector<int> coins{5, 10, 2, 1};
	int value = 52;

	EXPECT_EQ(6, minimumCoins(coins, value));

	coins = {18, 3, 5};
	value = 20;
	EXPECT_EQ(-1, minimumCoins(coins, value));
}

TEST(Greedy, MaximumActivitiesTest) {
	std::vector<std::pair<int, int>> activities{{3, 8}, {2, 4}, {1, 3}, {10, 11}};

	EXPECT_EQ(3, maximumActivities(activities));
}

TEST(Greedy, FractionalKnapsack) {
	std::vector<std::pair<int, int>> items{{50, 600}, {20, 500}, {30, 400}};

	int capacity = 70;

	EXPECT_EQ(1140, fractionalKnapsack(items, capacity));

	items = {{10, 200}, {5, 50}, {20, 100}};

	capacity = 15;

	EXPECT_EQ(250, fractionalKnapsack(items, capacity));
}

TEST(Greedy, JobSequencingTest) {
	std::vector<std::pair<int, int>> jobs{{4, 70}, {1, 80}, {1, 30}, {1, 100}};

	EXPECT_EQ(170, jobSequencing(jobs));

	jobs = {{4, 50}, {1, 5}, {1, 20}, {5, 10}, {5, 80}};

	EXPECT_EQ(160, jobSequencing(jobs));
}

TEST(Greedy, HuffmanTest) {
	std::vector<std::pair<char, int>> f{{'a', 10}, {'d', 50}, {'b', 20}, {'e',
			40}, {'f', 80}};

	buildHuffmanTree(f);
}

