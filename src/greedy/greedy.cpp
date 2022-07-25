/*
 * greedy.cpp
 *
 *  Created on: 30 May 2021
 *      Author: ykhan
 */

#include "greedy.h"

// find the minium number of coins that makeup a value
int minimumCoins(std::vector<int> coins, int value) {
	// sort in decreasing order
	std::sort(coins.begin(), coins.end(), [](const int& a, const int& b) {
		return a > b;
	});

	int count = 0;

	for (int i = 0; i < coins.size() && value; i++) {
		if (coins[i] <= value) {
			count += value / coins[i];
			value = value % coins[i];
		}
	}

	// if all coins checked and value is still > 0 it means
	// the value cannot be achieved through coins
	if (value)
		return -1;

	return count;
}

// time  O(nlogn), space O(1)
int maximumActivities(std::vector<std::pair<int, int>> activities) {
	// sort according to the increasing order of finish time
	// O(nlogn)
	std::sort(activities.begin(), activities.end(),
			[](std::pair<int, int>& a, std::pair<int, int>& b) {
				return a.second < b.second;
			});

	auto prev = activities[0];
	int count = 1;
	int maxCount = 0;

	// count non-overlapping O(n)
	for (int i = 1; i < activities.size(); i++) {
		auto curr = activities[i];
		if (curr.first >= prev.second) {
			count++;
			maxCount = std::max(maxCount, count);
			prev = curr;
		}
	}

	return maxCount;
}

// time O(nlogn) space O(1)
int fractionalKnapsack(vector<std::pair<int, int>> items, int capacity) {
	// sort according to per unit cost
	std::sort(items.begin(), items.end(), [](const auto& a, const auto& b) {
		int cost_a = a.second / a.first;
		int cost_b = b.second / b.first;

		return cost_a > cost_b;
	});

	int result = 0;

	for (int i = 0; i < items.size() && capacity > 0; i++) {
		const auto &[weight, values] = items[i];

		if (capacity >= weight) {
			result += values;
			capacity -= weight;
		} else {
			// fractional part
			result += static_cast<int>(values
					* (static_cast<float>(capacity) / weight));
			capacity = 0;
		}
	}

	return result;
}

int jobSequencing(std::vector<std::pair<int, int>> jobs) {
	// sort the jobs in increasing order of profits
	// O(nlogn)
	std::sort(jobs.begin(), jobs.end(), [](const auto& job1, const auto& job2) {
		auto &[deadline1, profit1] = job1;
		auto &[deadline2, profit2] = job2;

		return profit1 > profit2;
	});

	// O(n)
	int maxDeadline = std::accumulate(jobs.begin(), jobs.end(), 0,
			[](const auto& a, const auto& b) {
				return std::max(a, b.first);
			});

	int result = 0;

	// create slots upto maxDeadline
	// iterate over jobs, find an empty slot, add profit
	vector<bool> slotsAvailable(maxDeadline, true);

	// O(n^2)

	// TODO: use union-find or disjoint sets to reduce time complexity
	// for finding an empty slot
	// see https://www.geeksforgeeks.org/job-sequencing-using-disjoint-set-union/
	// and https://www.geeksforgeeks.org/union-find/
	for (int i = 0; i < jobs.size(); i++) {
		int desiredSlot = jobs[i].first - 1;
		for (int j = desiredSlot; j >= 0; j--) {
			if (slotsAvailable[j]) {
				slotsAvailable[j] = false;
				result += jobs[i].second;
				break;
			}
		}
	}

	return result;
}

std::shared_ptr<TreeNode<Huffman>> buildHuffmanTree(
		std::vector<std::pair<char, int>> frequency) {
	// sort according to increasing frequency
	std::sort(frequency.begin(), frequency.end(),
			[](const auto& a, const auto& b) {
				return a.second > b.second;
			});

	int total = std::accumulate(frequency.begin(), frequency.end(), 0,
			[](const int a, const auto b) {
				return a + b.second;
			});

	// TODO: study MinHeap to build the Huffman tree. Come back later

	return {};
}
