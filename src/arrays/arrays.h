#ifndef ARRAYS_H
#define ARRAYS_H

#include <vector>
#include <utility>

using namespace std;

// Given an array of numbers of length N, find both the minimum and maximum
// using less than 2 * (N - 2) comparisons or 2n - 4 comparisons
// the naive approach (compare each element with the min and max) gives 2(n-1)
// comparisons (start from arr[1] with min/max set to arr[0])

// Solution
// Time complexity of comparisons
// if n is even 1 + 3*(n-2 /2) = 1 + 1.5n -3 = 1.5n - 2
// if n is odd: 1 + 3*(n-2 /2) + 3 = 1 + 1.5n - 4.5 + 3 =  1.5n + 0.5 ~ 1.5n
pair<int , int> findMinMax(vector<int> arr);

// find the largest integer. O(n)
int largest(vector<int> vec);

// find the index of the largest integer. O(n)
int largestIndex(vector<int> vec);

// find second largest integer. O(n)
int secondLargest(vector<int> vec);

// find second largest integer index O(n)
int secondLargestIndex(vector<int> vec);

// check if an array is sorted in increasing or descending order O(n)
bool isSorted(vector<int> vec, bool ascending);

// reverse an array in place. O(n)
vector<int> reverse(vector<int>& vec);

// reverse part of the array from begin to end
vector<int> reverse(vector<int>& vec, int begin, int end);

// remove duplicates from an array. // remove duplicates from an array. Works for unsorted arrays O(n)
vector<int> removeDuplicates(vector<int> vec);

// move zeroes to end O(n)
vector<int> moveZeroesToEnd(vector<int> vec);

// rotate an array left by one place
vector<int> leftRotateByOne(vector<int> vec);

// rotate an array left by k places
vector<int> leftRotate(vector<int> vec, int k);

// find leaders in an array. A leader is an element with no greater element to its right (cannot be equal)
vector<int> leaders(vector<int> vec);

// find the maximum difference vec[j] - vec[i] such that j > i
int maxDifference(vector<int> vec);

// find the frequencies of elements in a sorted array
vector<std::pair<int, int>> frequenciesSorted(vector<int> vec);

// find the maximum profit in stocks
int maxProfitStocks(vector<int> vec);

// find the trapped rain water
int trappedRainWater(vector<int> vec);

// maximum consecutive 1's in a binary array
int maxConsecutiveOnes(vector<int> vec);

// int maximum sub array sum (kadane's algorithm)
int maxSubarraySum(vector<int> vec);

// maximum length even-odd array
int maxEvenOddArray(vector<int> vec);

// find the maximum circular subarray sum
int maxCircularSubarraySum(vector<int> vec);

// a majority element is an element, that appears more than n / 2 times in an array. Moore's voting algorithm
int findMajorityElement(vector<int> vec);

// find the maxium sum of k cosecutive elements
int maxSumKConsecutive(vector<int> vec, int k);

// check if a subarray with the given sum exists
bool subarrayWithSum(vector<int> vec, int targetSum);

// compute k n-bonnaci numbers
vector<int> computeKNBonnaci(int n, int k);

// find distinct elements in window of size k
vector<int> distinctElementsWindowSizeK(vector<int> vec, int k);

// return the min. group flips required for boolean array
vector<std::pair<int, int>> miniumGroupFlips(vector<int> vec);

// get sum of elements between start and end
int getSum(vector<int> vec, int start, int end);

// see if equilibrium point exists. Equilibrium point is an element whose left and right sum is equal
std::pair<bool, int> equilibriumExisits(vector<int> vec);

// find the maximum occurring element withing ranges
int maxOccuringInRanges(vector<int> left, vector<int> right);

// check if a given array can be divided into three parts with equal sum
bool divisibleThreePartsWithEqualSum(vector<int> vec);

// check if a given array contains a subarray with 0 sum
bool containsSubarrayWithZeroSum(vector<int> vec);

// find the longest subarray with equal number of 0's and 1's with a binary array
int longestSubarrayWithEqualOnesZeroes(vector<int> vec); 

// Just like std::remove
// Time O(n), space O(1)
vector<int>::iterator Remove(vector<int>::iterator begin, vector<int>::iterator end, int match);

#endif
