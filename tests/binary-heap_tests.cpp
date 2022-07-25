/*
 * binary-heap_tests.cpp
 *
 *  Created on: 16 Jul 2021
 *      Author: ykhan
 */

#include "../src/binary-heap/binary-heap.h"
#include <gtest/gtest.h>

TEST(BinaryHeap, MinHeapInsertTest) {
	MinHeap h;

	h.insert(3);
	h.insert(2);
	h.insert(15);
	h.insert(20);

	auto arr = h.array();

	EXPECT_EQ(arr[h.parent(1)], 2);
	EXPECT_EQ(arr[h.left(0)], 3);
	EXPECT_EQ(arr[h.right(0)], 15);
	EXPECT_EQ(arr[h.left(1)], 20);
}

TEST(BinaryHeap, MinHeapifyTest) {
	MinHeap h;

	std::vector<int> vec{40, 20, 30, 35, 25, 80, 32, 100, 70, 60};

	h.setArray(vec);

	h.minHeapify(0);

	std::vector<int> expected{20, 25, 30, 35, 40, 80, 32, 100, 70, 60};
	auto arr = h.array();

	EXPECT_EQ(arr, expected);
}

TEST(BinaryHeap, MinHeapExtractMinTest) {
	MinHeap h;

	std::vector<int> vec{20, 25, 30, 35, 40, 80, 32, 100, 70, 60};

	h.setArray(vec);

	int min = h.extractMinimum();

	EXPECT_EQ(min, 20);

	std::vector<int> expected{25, 35, 30, 60, 40, 80, 32, 100, 70};
	auto arr = h.array();

	EXPECT_EQ(arr, expected);
}

TEST(BinaryHeap, MinHeapDecreaseKeyTest) {
	MinHeap h;

	std::vector<int> vec{10, 20, 40, 80, 100, 70};

	h.setArray(vec);

	h.decreaseKey(3, 5);

	std::vector<int> expected{5, 10, 40, 20, 100, 70};
	auto arr = h.array();

	EXPECT_EQ(arr, expected);
}

TEST(BinaryHeap, MinHeapDeleteKeyTest) {
	MinHeap h;

	std::vector<int> vec{10, 20, 30, 40, 50, 35, 38, 45};

	h.setArray(vec);

	h.deleteKey(3);

	std::vector<int> expected{10, 20, 30, 45, 50, 35, 38};
	auto arr = h.array();

	EXPECT_EQ(arr, expected);
}

TEST(BinaryHeap, MinHeapBuildTest) {
	MinHeap h;

	std::vector<int> vec{10, 5, 20, 2, 4, 8};

	h.setArray(vec);

	h.build();

	std::vector<int> expected{2, 4, 8, 5, 10, 20};
	auto arr = h.array();

	EXPECT_EQ(arr, expected);
}

TEST(BinaryHeap, HeapSortIncreasingTest) {

	std::vector<int> vec{12, 11, 13, 5, 6, 7};
	;

	auto sorted = heapSort(vec);

	std::vector<int> expected{5, 6, 7, 11, 12, 13};

	EXPECT_EQ(sorted, expected);
}

TEST(BinaryHeap, SortKSortedTest) {
	int k = 3;
	std::vector<int> arr{2, 6, 3, 12, 56, 8};

	auto result = sortKSortedArray(arr, k);
	std::vector<int> expected{2, 3, 6, 8, 12, 56};

	EXPECT_EQ(result, expected);
}

TEST(BinaryHeap, PurchaseMaximumItemsWithSumTest) {
	std::vector<int> costs{1, 12, 5, 111, 200};
	int result = purchaseMaximumItemsWithSum(costs, 10);

	EXPECT_EQ(result, 2);

	costs = {20, 10, 5, 30, 100};
	result = purchaseMaximumItemsWithSum(costs, 35);

	EXPECT_EQ(result, 3);
}

TEST(BinaryHeap, KLargestElementsTest) {
	std::vector<int> arr{5, 15, 10, 20, 8};
	auto result = KLargestElements(arr, 2);

	std::vector<int> expected = {15, 20};

	EXPECT_EQ(result, expected);

	arr = {8, 6, 4, 10, 9};
	result = KLargestElements(arr, 3);

	expected = {8, 9, 10};

	EXPECT_EQ(result, expected);
}

TEST(BinaryHeap, KClosestElementsTest) {
	std::vector<int> arr{10, 15, 7, 3, 4};
	auto result = KClosestElements(arr, 8, 2);

	std::vector<int> expected = {10, 7};

	EXPECT_EQ(result, expected);

	arr = {100, 80, 10, 5, 70};
	result = KClosestElements(arr, 2, 3);

	expected = {70, 10, 5};

	arr = {10, 30, 5, 40, 38, 80, 70};

	result = KClosestElements(arr, 35, 3);

	expected = {40, 30, 38};

	EXPECT_EQ(result, expected);
}

TEST(BinaryHeap, mergeKSortedTest) {
	std::vector<std::vector<int>> arr{{10, 20}, {5, 15}, {4, 9, 11}};

	auto result = mergeKsortedArrays(arr);

	std::vector<int> expected = {4, 5, 9, 10, 11, 15, 20};

	EXPECT_EQ(result, expected);
}

TEST(BinaryHeap, MedianOfStreamTest) {
	std::vector<int> arr{12, 15, 10, 5, 8, 7, 16};

	std::vector<double> result = medianOfAStream(arr);

	std::vector<double> expected{12, 13.5, 12, 11, 10, 9, 10};

	EXPECT_EQ(result, expected);
}
