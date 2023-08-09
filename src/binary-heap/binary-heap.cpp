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

// make sure to check on bounds at call site
int BinaryHeap::left(int i)
{
	return 2 * i + 1;
}

// make sure to check on bounds at call site
int BinaryHeap::right(int i)
{
	return 2 * i + 2;
}

// make sure to check on bounds at call site
int BinaryHeap::parent(int i)
{
	return (i - 1) / 2;
}

std::vector<int> BinaryHeap::array()
{
	return this->arr;
}

void BinaryHeap::setArray(std::vector<int> arr)
{
	this->arr = arr;
}

void MinHeap::insert(int value)
{
	// insert into the next empty slot (filling the level left-to-right
	arr.push_back(value);

	int currIdx = arr.size() - 1;
	int parentIdx = parent(currIdx);

	// now make sure it follows the min heap property
	while (arr[currIdx] < arr[parentIdx])
	{
		swap(arr[currIdx], arr[parentIdx]);
		currIdx = parentIdx;
	}
}

void MinHeap::heapify(int index)
{
	int currIdx = index;
	int minIdx = index;
	int n = arr.size();

	auto findMinimum = [&](int root, int left, int right)
	{
		int minIdx = root;
		if (left < n && arr[left] < arr[minIdx])
			minIdx = left;
		if (right < n && arr[right] < arr[minIdx])
			minIdx = right;
		return minIdx;
	};

	// iterative solution, check MaxHeap for recursive implementation with O(logn) space
	while ((minIdx = findMinimum(currIdx, left(currIdx), right(currIdx))) != currIdx)
	{
		swap(arr[currIdx], arr[minIdx]);
		currIdx = minIdx;
	}
}

int MinHeap::getMinimum()
{
	if (arr.size() > 0)
		return arr[0];
	else
		return INT_MAX;
}

int MinHeap::extractMinimum()
{
	int ret = INT_MAX;

	if (arr.size() == 0)
		return INT_MAX;

	if (arr.size() == 1)
	{
		ret = arr[0];
		arr.pop_back();
		return ret;
	}

	int last = arr.size() - 1;

	if (arr.size() > 1)
	{
		ret = arr[0];
		// swap the root with the last element
		std::swap(arr[0], arr[last]);
		// remove last element from the array
		arr.pop_back();
		// this swapping might have introduced violate at the root now
		heapify(0);
	}

	return ret;
}

// replace existing value with a lower one, violating minheap properties
void MinHeap::decreaseKey(int index, int value)
{
	if (index <= 0 || index > arr.size())
	{
		return;
	}

	int currIdx = index;

	arr[currIdx] = value;

	// Just like insert, move the value up the tree
	while (currIdx != 0 && arr[currIdx] < arr[parent(currIdx)])
	{
		swap(arr[currIdx], arr[parent(currIdx)]);
		currIdx = parent(currIdx);
	}
}

void MinHeap::deleteKey(int deleteIndex)
{
	// make the node to be removed shorted so it moves to the top
	decreaseKey(deleteIndex, INT_MIN); // O(logn)
	// remove the root node
	extractMinimum(); // O(logn)
}

void MinHeap::build()
{
	// we have to heapify the internal nodes (non-leaf nodes)
	// starting from the last internal node (parent of last node)
	int last = arr.size() - 1;
	for (int i = parent(last); i >= 0; i--)
	{
		heapify(i);
	}

	// starting from bottom-to-up make sure when we process top nodes,
	// the bottom trees have been heapifed properly.
}
/* O(logn)
   Worst-case, the item being inserted is the maxium and need to bubble up to the root
   of the tree
*/
void MaxHeap::insert(int value)
{
	arr.push_back(value);

	int currIdx = arr.size() - 1;
	int parentIdx = parent(currIdx);

	// now make sure it follows the min heap property
	while (arr[currIdx] > arr[parentIdx])
	{
		swap(arr[currIdx], arr[parentIdx]);
		currIdx = parentIdx;
	}
}

void MaxHeap::heapify(int index)
{
	int leftIdx = left(index);	 // make sure it is a valid index
	int rightIdx = right(index); // make sure it is a valid index
	int maxIdx = index;			 // index of largest value
	int n = arr.size();

	// Find the largest of currIdx (index), leftIdx, and rightIdx
	if (leftIdx < n && arr[leftIdx] > arr[maxIdx])
		maxIdx = leftIdx;

	if (rightIdx < n && arr[rightIdx] > arr[maxIdx])
		maxIdx = rightIdx;

	// needs adjustment
	if (maxIdx != index)
	{
		std::swap(arr[index], arr[maxIdx]);
		// adjust the subtree
		heapify(maxIdx);
	}
}

int MaxHeap::getMaximum()
{
	if (arr.size() > 0)
		return arr[0];
	else
		return INT_MIN;
}

int MaxHeap::extractMaximum()
{
	int maximum = INT_MIN;

	if (arr.size() == 0)
		return INT_MIN;

	if (arr.size() == 1)
	{
		maximum = arr[0];
		arr.pop_back();
		return maximum;
	}

	maximum = arr[0];
	int last = arr.size() - 1;
	std::swap(arr[0], arr[last]); // smallest becomes the root, heapify
	arr.pop_back();

	heapify(0);

	return maximum;
}

void MaxHeap::increaseKey(int index, int value)
{
	arr[index] = value;

	for (int i = index; i >= 0 && arr[parent(i)] < arr[i]; i = parent(i))
	{
		std::swap(arr[i], arr[parent(i)]);
	}
}

void MaxHeap::deleteKey(int i)
{
	increaseKey(i, INT_MAX);
	extractMaximum();
}

void MaxHeap::build()
{
	int last = arr.size() - 1;

	for (int i = parent(last); i >= 0; i--)
	{
		heapify(i);
	}
}

std::vector<int> heapSort(std::vector<int> vec)
{
	MaxHeap h;
	vector<int> sorted(vec.size(), 0);
	h.setArray(vec);
	h.build(); // O(nlogn) but mathematically proven to be O(n), see lecture
	/*
	  Note: in order to use the same internal array of MaxHeap instead
	  of creating a new sorted array, the heapify function needs to be
	  modified to take range of array elements that make up the heap e.g.
	  heapify(start, end) so that the sorted elements that are already
	  at the correct place (beginning from last_index) can be ignored.
	*/
	for (int i = vec.size() - 1; i >= 0; i--)
	{
		sorted[i] = h.extractMaximum(); // O(logn)
	}

	return sorted;
}

// K sorted array, an element in the original array
// can be k positions off from it's original positions in the final array
// That means item at index 0 in original array can be at 0 to k in the
// final sorted array

// idea maintain a minheap of k elements at a time
std::vector<int> sortKSortedArray(std::vector<int> arr, int k)
{
	// trick: the element at index 0 can either be at 0 or k
	// to determine it, we need comparison between k+1 elements

	// Implementation 1:
	// priority_queue<int, vector<int>, greater<int>> pq;
	// vector<int> sorted(arr.size(), -1);
	// for (int i = 0; i < k + 1; i++)
	// {
	// 	pq.push(arr[i]);
	// }

	// for (int i = 0; i < arr.size(); i++)
	// {
	// 	sorted[i] = pq.top();
	// 	pq.pop();
	// 	if (i < arr.size() - k - 1)
	// 		pq.push(arr[i + k + 1]);
	// }

	// return sorted;

	// Implementation 2:
	priority_queue<int, vector<int>, greater<int>> pq;
	vector<int> sorted;
	// O(klogk)
	for (int i = 0; i <= k; i++)
	{
		pq.push(arr[i]);
	}

	// O((n-k)logk)
	for (int i = k + 1; i < arr.size(); i++)
	{
		sorted.push_back(pq.top());
		pq.pop();
		pq.push(arr[i]);
	}

	// O(klogk)
	while (!pq.empty())
	{
		sorted.push_back(pq.top());
		pq.pop();
	}

	return sorted;
}

// Time O(nlogn) worst case, space O(n)
int purchaseMaximumItemsWithSum(std::vector<int> costs, int sum)
{
	// One way is to sorted the whole costs array with O(nlogn)
	// However, we could use min heap
	// Build a minheap O(n) (see lecture to know why it is not O(nlogn))
	// Find the minimum cost from the heap O(logn)
	// If cost is less than sum, add 1 to result and subtract it from sum O(1)
	// if sum is greater than 0 and items remain, repeat above
	// In this case time complexity could be less than O(nlogn) i.e. O(result
	// if sum quickly
	// reaches 0. If the sum is infinite then complexity reaches O(nlogn)
	priority_queue<int, vector<int>, greater<int>> pq(costs.begin(),
													  costs.end()); // O(n)

	int result = 0;

	while (sum > 0 && !pq.empty())
	{
		int cost = pq.top();
		pq.pop();

		if (sum >= cost)
		{
			result++;
			sum -= cost;
		}
	}

	return result;
}

// Time O(k + (n-k)logk) space O(k)
std::vector<int> KLargestElements(std::vector<int> arr, int k)
{
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
	// So minheap actually consists of k max elements where root
	// is the minimum of those k max elements. For example
	// for {1, 2, 3, 4, 5} and k = 3, the root will be
	// 3 and it is the lowest of k max elements 3, 4, 5
	// important point to consider is that in minheap root is lowest
	// so we need to make sure the root is the lowest max i.e
	// minimize the max root
	priority_queue<int, vector<int>, greater<int>> pq(arr.begin(),
													  arr.begin() + k); // O(k)

	// O((n-k)logk)
	for (int i = k; i < arr.size(); i++)
	{
		int top = pq.top();
		if (arr[i] > top)
		{
			pq.pop();		 // O(logk)
			pq.push(arr[i]); // O(logk)
		}
	}

	while (!pq.empty())
	{
		result.push_back(pq.top());
		pq.pop();
	}

	return result;
}

// Time O(nlogk)
std::vector<int> KClosestElements(std::vector<int> arr, int n, int k)
{
	// a heap that contains k lowest differences
	// that means we need to minimize the root of max heap
	// root contains max difference, which means
	// other k-1 differences are lower than root

	priority_queue<pair<int, int>> pq;
	vector<int> result;

	// building heap: O(klogk)
	for (int i = 0; i < k; i++)
	{
		pq.push(pair<int, int>{abs(arr[i] - n), i});
	}

	// O((n-k)*logk)
	for (int i = k; i < arr.size(); i++)
	{
		int difference = abs(arr[i] - n);
		if (difference < pq.top().first)
		{
			pq.pop();
			pq.push({difference, i});
		}
	}
	// O(klogk)
	while (!pq.empty())
	{
		result.push_back(arr[pq.top().second]);
		pq.pop();
	}

	return result;
}

std::vector<int> mergeKsortedArrays(std::vector<std::vector<int>> arr)
{
	struct Data
	{
		int value;
		int arrayIndex;
		int valueIndex;
	};

	struct MergeComp
	{
		bool operator()(Data a, Data b)
		{
			return a.value > b.value;
		}
	};

	vector<int> result;
	int k = arr.size();

	// store 1 element from each array into a heap, it will give us a minimum of all k arrays
	priority_queue<Data, vector<Data>, MergeComp> pq;
	// enter first element of each vector into the priority queue
	for (int i = 0; i < k; i++)
	{
		Data d{arr[i][0], i, 0};
		pq.push(d);
	}

	while (!pq.empty())
	{
		auto [value, arrayIndex, valueIndex] = pq.top();
		pq.pop();
		result.push_back(value);

		// add the next value from the same array, if it exists
		valueIndex = valueIndex + 1;

		if (valueIndex < arr[arrayIndex].size())
		{
			pq.push({arr[arrayIndex][valueIndex], arrayIndex, valueIndex});
		}
	}

	return result;
}

// median is a value that is greater than half of the values and smaller than
// half of the values
// Time O(nlogn)
std::vector<double> medianOfAStream(std::vector<int> arr)
{
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
	priority_queue<int> left;							  // maxheap
	priority_queue<int, vector<int>, greater<int>> right; // minheap
	std::vector<double> medians;

	// enter one element in left
	left.push(arr[0]);
	medians.push_back(arr[0]);

	for (int i = 1; i < arr.size(); i++)
	{
		// if size of left is already one more than right
		if (left.size() > right.size())
		{
			// an item must be added to the right to make both left and right
			// halves equal in size
			if (arr[i] > left.top()) // if new item is greater than the max in left
			{
				right.push(arr[i]);
			}
			else
			{
				// move max item from left to right and put this in left
				right.push(left.top());
				left.pop();
				left.push(arr[i]);
			}
			medians.push_back((left.top() + right.top()) / 2.0);
		}
		else
		{
			// an item must be added to the left
			if (arr[i] < right.top())
			{
				left.push(arr[i]);
			}
			else
			{
				left.push(right.top());
				right.pop();
				right.push(arr[i]);
			}
			medians.push_back(left.top());
		}
	}

	return medians;
}
