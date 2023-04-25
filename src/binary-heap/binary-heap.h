/*
 * binary-heap.h
 *
 *  Created on: 27 Jun 2021
 *      Author: ykhan
 */

#ifndef BINARY_HEAP_BINARY_HEAP_H_
#define BINARY_HEAP_BINARY_HEAP_H_

/*
 * Binary heap data structure is used:
 * 1. To implement Heapsort
 * 2. To implement priority queue
 *
 * It has two types:
 * 1. Min Heap
 * Highest priority item is assigned lowest value
 *
 * 2. Max Heap
 * Highest priority item is assigned highest value
 *
 * Binary Heap is a complete binary tree (stored as an array)
 * A full binary tree is one in which leaf nodes has 0 children and
 * all other nodes have exactly 2 children. In other words, each node has
 * either 0 or 2 children.
 *
 * A complete binary tree is the one which has all levels completely filled
 * and the last level might be incomplete and filled from left to right
 *
 * About storing binary tree as an array, you can think of how inorder, preorder
 * or postorder traversal can also be stored as an array and can be used to
 * represent the tree.
 *
 * The binary heap must be considered as a complete binary tree in order to store
 * it as an array. As the levels are filled left to right, we can predict the indices
 * for the left and right child from the array.
 *
 * for a node i, indices can be found as
 * left = 2*i + 1
 * right = 2*i + 2
 * parent = ceil(i - 1)/2
 *
 * NOTE: A key point to remember is that a heap is an array with special consideration to how elements
 * are indexed i.e. instead of finding elements linearly using consecutive index, use the above
 * left, right and parent index calculation to traverse array. I have created special MinHeap and MaxHeap
 * classes to abstract away the details but you could do even without them and just have functions that
 * operate on arrays like
 *
 * heapify(int arr[], int i, int n)
 * extractMinimum(int arr[], int n)
 * build(int arr[], int n)
 * etc
 *
 * The important premise for Heapify, there is a Binary Heap
 * with only 1 discrepancy i.e. one node is out of order and
 * the rest of the tree follows the rule.
 *
 * Advantages:
 * 1. Random access (stored as an array) O(1)
 * 2. Cache friendly (locality of reference)
 * 3. Height of tree is minimum possible
 * 4. No space needed for storing left and right pointers
 *
 * Note that binary heap is not necessarily a BST where left is less than root and right is greater than root
 *
 * Min Heap:
 * 1. A complete binary tree
 * 2. Every node has a value smaller than its descendents. So root must be the minimum value
 *
 */

/*
 * Priority Queue Applications:
 * 1. Dijkstra Algorithm
 * 2. Prim Algorithm
 * 3. Huffman Algorithm
 * 4. HeapSort
 */

/*
 * Priority Queue in C++:
 * A priority queue is always implemented using a heap data structure.
 *
 * Creating a Priority Queue (MaxHeap):
 * #include <queue>
 * std::priority_queue<int> pq; // default is MaxHeap
 *
 * Normal queue functions except highest values always at top
 * pq.top()
 * pq.pop()
 * pq.empty()
 * pq.size()
 *
 * Creating a Priority Queue (MinHeap)
 *
 * std::priority_queue<int, 			// underlying datatype
 *  				   vector<int>, 	// underlying array for implementation (must specify)
 *  				   greater<int>		// comparator
 *  				  > pq;
 *
 * Example:
 *
 * #include <iostream>
 * #include <queue>
 *
 * using namespace std;
 *
 * int main() {
 * 	   using namespace std;
 *
 *     int arr[] {10, 5, 15};
 *     priority_queue<int> pq(arr, arr + 3); // build O(n)
 *      // or
 *     priority_queue<int, vector<int>, greater<int>> pq2(begin(arr), end(arr));
 *
 *     while (!pq.empty()) {
 *         cout << pq.top() << ", "; // O(1)
 *         pq.pop();                 // O(logn) push is also O(logn)
 *     }
 *
 *     cout << endl;
 *
 *     while (!pq2.empty()) {
 *         cout << pq2.top() << endl;
 *         pq2.pop();
 *     }
 * }
 *
 * Output:
 * 15, 10, 5,
 * 5, 10, 15,
 */

/*
 * If priority queue is created with std::pair<int, int> data type, the first element of the pair
 * is considered for min/max by the default comparators. To override this behavior, provide custom
 * comparators (function objects that overload operator() and return a bool)
 */

#include <vector>
#include <queue>

class BinaryHeap {
protected:
	std::vector<int> arr{};
public:
	int left(int i);
	int right(int i);
	int parent(int i);

	// for debugging
	std::vector<int> array();
	void setArray(std::vector<int> arr);

	virtual void insert(int value) = 0;
	virtual ~BinaryHeap() {}

};

class MinHeap: public BinaryHeap {
public:
	void insert(int value) override;
	// Time O(logn), space O(logn)
	void minHeapify(int i); // i is the node which possibly violates the minheap property and fixes it
	// Time O(1) space O(1)
	int getMinimum();
	// Time O(logn), space O(logn)
	int extractMinimum(); // remove the minimum element from the min heap
	// Time O(logn) space O(1)
	void decreaseKey(int index, int value); // replace existing value with a lower value,
	// Time O(logn) space O(1)
	void deleteKey(int i); // delete a value at index i
	// Time upper bounded by O(nlogn) but mathematically for complete binary tree O(n), see lecture
	void build(); // given a minheap with random ordered array, make sure the whole tree is a minheap
};

class MaxHeap: public BinaryHeap {
public:
	void insert(int value) override;
	// Time O(logn), space O(logn)
	void maxHeapify(int i); // i is the node which possibly violates the maxheap property and fixes it
	void maxHeapify(int i, int size);
	// Time O(1) space O(1)
	int getMaximum();
	// Time O(logn), space O(logn)
	int extractMaximum(); // remove the maximum element from the max heap
	// Time O(logn) space O(1)
	void increaseKey(int index, int value); // replace existing value with a higher value,
	// Time O(logn) space O(1)
	void deleteKey(int i); // delete a value at index i
	// Time upper bounded by O(nlogn) but mathematically for complete binary tree O(n), see lecture
	void build(); // given a maxheap with random ordered array, make sure the whole tree is a maxheap
	std::vector<int> heapSort();
};

// heapSort is based on the idea of selection sort
// In the case of sorting into ascending order using selection sort,
// we first find the maximum value O(n^2), and put it at the last index
// In case of maxHeap, the maximum value is always present at top so
// we can get maximum in O(1), put it at the last index and heapiify the
// disturbed maxheap O(logn). So instead of O(n^2), time complexity of
// heapSort is O(nlogn)
std::vector<int> heapSort(std::vector<int> vec);

// In layman terms: a K-sorted array is an array that is sorted in segments i.e.
// not fully sorted. The extent of how much it is sorted is quantified by k
// which means that once you fully sort the k-sorted array, the
// item at index i in k-sorted array will be present between indices
// i-k to i+k in the final fully sorted array.
// e.g.
// input[] = {9, 8, 7, 18, 19, 17}, k = 2
// Input element	orig idx		possible indices in the output (in other words it could be minimum of these indices from original array)
// 		9				0				0 to 2
// 		8				1				0 to 3
// 		7				2				0 to 4
// 		18				3				1 to 5
// 		19				4				2 to 5
// 		17				5				3 to 5
// output = {7, 8, 9, 17, 18, 19};
// Idea: maintain a min heap of size k + 1 i.e. 3 nodes participate in a minheap at at time
// You get a minimum value out and add a new value to the heap
// Time O((n-k)logk), space O(k)
std::vector<int> sortKSortedArray(std::vector<int> arr, int k);

// return the maximum number of items that can be purchased using the given sum and array of costs
int purchaseMaximumItemsWithSum(std::vector<int> costs, int sum);

// Find the k largest elements from an array
std::vector<int> KLargestElements(std::vector<int> arr, int k);

std::vector<int> KClosestElements(std::vector<int> arr, int n, int k);

std::vector<int> mergeKsortedArrays(std::vector<std::vector<int>> arr);

std::vector<double> medianOfAStream(std::vector<int> arr);

#endif /* BINARY_HEAP_BINARY_HEAP_H_ */
