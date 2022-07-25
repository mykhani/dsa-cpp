/*
 * binary-heap.cpp
 *
 *  Created on: 27 Jun 2021
 *      Author: ykhan
 */

#include "binary-heap.h"
#include <climits>
#include <utility>
#include <cmath>

using namespace std;

int BinaryHeap::left(int i) {
	unsigned int index = 2 * i + 1;

	return index;
}

int BinaryHeap::right(int i) {
	unsigned int index = 2 * i + 2;

	return index;
}

int BinaryHeap::parent(int i) {
	unsigned int index = (i - 1) / 2;

	return index;
}

std::vector<int> BinaryHeap::array() {
	return this->arr;
}

void BinaryHeap::setArray(std::vector<int> arr) {
	this->arr = arr;
}

void MinHeap::insert(int value) {
	// insert into the next empty slot (filling the level left-to-right
	arr.push_back(value);

	int size = arr.size();
	// now make sure it follows the min heap property
	for (int i = size - 1; i > 0 && arr[parent(i)] > arr[i]; i = parent(i)) {
		std::swap(arr[i], arr[parent(i)]);
	}
}

void MinHeap::minHeapify(int i) {
	int leftIdx = left(i);
	int rightIdx = right(i);
	int leftVal = INT_MAX;
	int rightVal = INT_MAX;

	int smallest = i;
	int n = arr.size();
	// find the smallest of the current node and its left and right

	if (leftIdx < n && arr[leftIdx] < arr[smallest])
		smallest = leftIdx;

	if (rightIdx < n && arr[rightIdx] < arr[smallest])
		smallest = rightIdx;

	if (smallest != i) {
		std::swap(arr[smallest], arr[i]);
		// check if swapping caused any minheap violation in the left subtree
		minHeapify(smallest);
	}
}

int MinHeap::getMinimum() {
	if (arr.size() > 0)
		return arr[0];
	else
		return INT_MAX;
}

int MinHeap::extractMinimum() {
	int ret = INT_MAX;

	if (arr.size() == 0)
		return INT_MAX;

	if (arr.size() == 1) {
		ret = arr[0];
		arr.pop_back();
		return ret;
	}

	int last = arr.size() - 1;

	if (arr.size() > 1) {
		ret = arr[0];
		// swap the root with the last element
		std::swap(arr[0], arr[last]);
		// remove last element from the array
		arr.pop_back();
		// this swapping might have introduced violate at the root now
		minHeapify(0);
	}

	return ret;
}

// replace existing value with a lower one, violating minheap properties
void MinHeap::decreaseKey(int index, int value) {
	arr[index] = value;

	for (int i = index; i >= 0 && arr[parent(i)] > arr[i]; i = parent(i)) {
		std::swap(arr[i], arr[parent(i)]);
	}
}

void MinHeap::deleteKey(int deleteIndex) {
	// make the node to be removed shorted so it moves to the top
	decreaseKey(deleteIndex, INT_MIN); // O(logn)
	// remove the root node
	extractMinimum(); // O(logn)
}

void MinHeap::build() {
	// we have to heapify the internal nodes (non-leaf nodes)
	// starting from the last internal node (parent of last node)
	int last = arr.size() - 1;
	for (int i = parent(last); i >= 0; i--) {
		minHeapify(i);
	}

	// starting from bottom-to-up make sure when we process top nodes,
	// the bottom trees have been heapifed properly.
}

std::vector<int> MaxHeap::heapSort() {
	int size = arr.size();

	build(); // O(n); make sure the array follows maxHeap properties

	for (int i = size - 1; i > 0; i--) {
		int max = arr[0];
		std::swap(arr[i], arr[0]);
		maxHeapify(0, i); // O(logn)
	}

	return arr;
}

void MaxHeap::insert(int value) {
	arr.push_back(value);

	for (int i = arr.size() - 1; i >= 0 && arr[i] > arr[parent(i)];
			i = parent(i)) {
		std::swap(arr[i], arr[parent(i)]);
	}
}

void MaxHeap::maxHeapify(int i) {
	int largest = i; // index of largest value
	int n = arr.size();

	int leftIdx = left(i);
	int rightIdx = right(i);

	if (leftIdx < n && arr[leftIdx] > arr[i])
		largest = leftIdx;

	if (rightIdx < n && arr[rightIdx] > arr[i])
		largest = rightIdx;

	// needs adjustment
	if (largest != i) {
		std::swap(arr[i], arr[largest]);
		// adjust the subtree
		maxHeapify(largest);
	}
}

void MaxHeap::maxHeapify(int i, int n) {
	int largest = i; // index of largest value

	int leftIdx = left(i);
	int rightIdx = right(i);

	if (leftIdx < n && arr[leftIdx] > arr[largest])
		largest = leftIdx;

	if (rightIdx < n && arr[rightIdx] > arr[largest])
		largest = rightIdx;

	// needs adjustment
	if (largest != i) {
		std::swap(arr[i], arr[largest]);
		// adjust the subtree
		maxHeapify(largest, n);
	}
}

int MaxHeap::getMaximum() {
	if (arr.size() > 0)
		return arr[0];
	else
		return INT_MIN;
}

int MaxHeap::extractMaximum() {
	int maximum = INT_MIN;

	if (arr.size() == 0)
		return INT_MIN;

	if (arr.size() == 1) {
		maximum = arr[0];
		arr.pop_back();
		return maximum;
	}

	maximum = arr[0];
	int last = arr.size() - 1;
	std::swap(arr[0], last); // smallest becomes the root, heapify
	arr.pop_back();

	maxHeapify(0);

	return maximum;
}

void MaxHeap::increaseKey(int index, int value) {
	arr[index] = value;

	for (int i = index; i >= 0 && arr[parent(i)] < arr[i]; i = parent(i)) {
		std::swap(arr[i], arr[parent(i)]);
	}
}

void MaxHeap::deleteKey(int i) {
	increaseKey(i, INT_MAX);
	extractMaximum();
}

void MaxHeap::build() {
	int last = arr.size() - 1;

	for (int i = parent(last); i >= 0; i--) {
		maxHeapify(i);
	}
}

std::vector<int> heapSort(std::vector<int> vec) {
	MaxHeap h;
	h.setArray(vec);

	return h.heapSort();
}

std::vector<int> sortKSortedArray(std::vector<int> arr, int k) {
	priority_queue<int, vector<int>, greater<int>> pq;
	std::vector<int> result;

	// O(klogk)
	for (int i = 0; i <= k; i++) {
		pq.push(arr[i]);
	}

	// O((n-k)logk)
	for (int i = k + 1; i < arr.size(); i++) {
		int minimum = pq.top();
		pq.pop();

		result.push_back(minimum);
		pq.push(arr[i]);
	}

	// O(klogk)
	while (!pq.empty()) {
		int minimum = pq.top();
		pq.pop();
		result.push_back(minimum);
	}

	return result;
}

// Time O(nlogn) worst case, space O(n)
int purchaseMaximumItemsWithSum(std::vector<int> costs, int sum) {
	// One way is to sorted the whole costs array with O(nlogn)
	// However, we could use min heap
	// Build a minheap O(n)
	// Find the minimum cost from the heap O(logn)
	// If cost is less than sum, add 1 to result and subtract it from sum O(1)
	// if sum is greater than 0 and items remain, repeat above
	// In this case time complexity could be less than O(nlogn) if sum quickly
	// reaches 0. If the sum is infinite then complexity reaches O(nlogn)
	priority_queue<int, vector<int>, greater<int>> pq(costs.begin(),
			costs.end()); // O(n)

	int result = 0;

	while (sum > 0 && !pq.empty()) {
		int cost = pq.top();
		pq.pop();

		if (sum >= cost) {
			result++;
			sum -= cost;
		}
	}

	return result;
}

// Time O(k + (n-k)logk) space O(k)
std::vector<int> KLargestElements(std::vector<int> arr, int k) {
	vector<int> result;

	// Time O(n + klogn)
//	priority_queue<int> pq(arr.begin(), arr.end()); // O(n)
//
//	for (int i = 0; i < k; i++) {
//		result.push_back(pq.top());
//		pq.pop();
//	}

	// Keep a min heap of k elements, root has the smallest value
	// meaning other elements are greater or K larger elements
	// of we encounter a value greater than root, make it root
	// and heapify
	priority_queue<int, vector<int>, greater<int>> pq(arr.begin(),
			arr.begin() + k); // O(k)

	// O((n-k)logk)
	for (int i = k; i < arr.size(); i++) {
		int top = pq.top();
		if (arr[i] > top) {
			pq.pop(); 		 // O(logk)
			pq.push(arr[i]); // O(logk)
		}
	}

	while (!pq.empty()) {
		result.push_back(pq.top());
		pq.pop();
	}

	return result;
}

struct Comparison {
	bool operator()(pair<int, int> a, pair<int, int> b) {
		return a.first <= b.first;
	}
};

std::vector<int> KClosestElements(std::vector<int> arr, int n, int k) {
	// what if I create a max heap of difference with k, replace root
	priority_queue<pair<int, int>, vector<pair<int, int>>, Comparison> pq;
//	priority_queue<pair<int, int>> pq; // max heap

	vector<int> result;

	int difference = INT_MAX;

	// O(klogk)
	for (int i = 0; i < k; i++) {
		difference = abs(arr[i] - n);
		pq.push({difference, i});
	}

	// O((n-k)logk)
	for (int i = k; i < arr.size(); i++) {
		difference = abs(arr[i] - n);
		if (difference < pq.top().first) {
			pq.pop();
			pq.push({difference, i});
		}
	}

	// O(klogk)
	while (!pq.empty()) {
		result.push_back(arr[pq.top().second]);
		pq.pop();
	}

	return result;
}

std::vector<int> mergeKsortedArrays(std::vector<std::vector<int> > arr) {
	struct Data {
		int value;
		int arrayIndex;
		int valueIndex;
	};

	struct MergeComp {
		bool operator()(Data a, Data b) {
			return a.value > b.value;
		}
	};

	vector<int> result;
	int k = arr.size();

	// store 1 element from each array into a heap, it will give us a minimum of all k arrays
	priority_queue<Data, vector<Data>, MergeComp> pq;
	// enter first element of each vector into the priority queue
	for (int i = 0; i < k; i++) {
		Data d{arr[i][0], i, 0};
		pq.push(d);
	}

	while (!pq.empty()) {
		auto [value, arrayIndex, valueIndex] = pq.top();
		pq.pop();
		result.push_back(value);

		// add the next value from the same array, if it exists
		valueIndex = valueIndex + 1;

		if (valueIndex < arr[arrayIndex].size()) {
			pq.push({arr[arrayIndex][valueIndex], arrayIndex, valueIndex});
		}
	}

	return result;
}

std::vector<double> medianOfAStream(std::vector<int> arr) {
	// A median divides a sorted array into left and right halves
	// where left half is less than median while right half is greater
	// than median. The idea is to represent these halves as two
	// heaps. We fill the left heap first and then the right one.
	// The goal is to make the sizes same if possible or the left
	// side has one more element
	// If the total number of elements in array is odd, then the
	// median is the highest element in the left side
	// If total number of elements is even, the median is
	// highest value in left plus lowest value in right whole
	// divided by 2
	priority_queue<int> left; // maxheap
	priority_queue<int, vector<int>, greater<int>> right;

	std::vector<double> medians;

	// enter one element in left
	left.push(arr[0]);
	medians.push_back(arr[0]);

	for (int i = 1; i < arr.size(); i++) {
		// if  left part becomes greater than right
		if (left.size() > right.size()) {
			// see if x should go to the left or right
			if (left.top() < arr[i]) {
				right.push(arr[i]);
			} else {
				right.push(left.top());
				left.pop();
				left.push(arr[i]);
			}
			medians.push_back((left.top() + right.top())/2.0);
		// if left part's size is equal or less than right size
		} else {
			if (arr[i] > right.top()) {
				left.push(right.top());
				right.pop();
				right.push(arr[i]);
			} else {
				left.push(arr[i]);
			}
			medians.push_back(left.top());
		}
	}

	return medians;
}
