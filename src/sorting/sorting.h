#ifndef SORTING_H
#define SORTING_H

#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>

using namespace std;

// sort an integer array using STL. C++ sort function uses quick sort internally worst case O(nlogn) by default
// if quicksort is doing unfair partitioning and taking more time, it switches to heap sort and
// when array size is very small, it uses insertion sort
void sortArraySTL(int arr[], int size);
void sortArraySTL(int arr[], int size, std::function<bool(int, int)> compare_fn);

// Stable sort:
// Suppose there is a vector of objects, and some property of objects is used to sort them,
// then a stable sort is the output where two objects having same key (sorting criteria) are
// in the same sequence as in the original array.
//
// Unstable sort:
// Contrary to the above, the order of elements of same key can be different than in their
// original array.

// Examples of stable sort algorithms:
// Bubble sort, insertion sort, mergesort
//
// Examples of unstable sort:
// Selection sort, heap sort, quicksort

// O(n^2)
vector<int> bubbleSort(vector<int> vec);

// O(n^2). Pros: does less memory writes compared to quicksort, mergesort, insertion rate
// But cycle sort is optimal in terms of memory writes
// Memory writes can be expensive, in case of Flash or EEPROM as there a finite write cycles.
vector<int> selectionSort(vector<int> vec);

// O(n^2)
void InsertionSort(vector<int> &arr);

// find intersection of two sorted arrays
vector<int> interSectionSortedArrays(vector<int> vec1, vector<int> vec2);

// find the union of two sorted arrays
vector<int> unionSortedArrays(vector<int> vec1, vector<int> vec2);

// count inversions. Inversion is condition where a[i] > a[j] for i < j. Time: O(nlogn), space: O(n)
int countInversions(vector<int> vec);

// time: O(nlogn), space O(n)
void MergeSort(vector<int> &arr);

/*
 *  Quick sort
 * 1. Divide and conquer algorithm
 * 2. Worst-case time O(n^2)
 * 3. Despite O(n^2), it is considered faster because:
 *    i. in place
 *   ii. cache friendly
 *  iii. Average case is O(nlogn)
 *   iv. Tail recursive
 *
 * Both quick sort and merge sort are divide and conquer.
 * In quick sort, the divide part is complex
 * In merge sort, the merge part is complex
 * */

// Simplest Quicksort where pivot is chosen as the last element in the subarray
// worst case time: O(n^2) space: O(n) (when array is already sorted)
// best case time: O(nlogn space: O(logn) (when partitioning divides array into equal halves)
void QuickSort(vector<int> &arr);

#endif