#ifndef SEARCHING_H
#define SEARCHING_H

#include <vector>
#include <numeric>

using namespace std;

// using iterative binary search, find the index of number x in array. Time O(logn), space O(1)
int binarySearchIter(vector<int> vec, int x);

// using recursive binary search, find the index of number x in array. Time O(logn), space O(logn)
int binarySearchRec(vector<int> vec, int x, int p, int q);

// find the index of first occurrence
int findIndexFirstOccurrence(vector<int> vec, int x);

// find index of last occurrence
int findIndexLastOccurrence(vector<int> vec, int x);

// count the total occurrences of the number
int findTotalOccurrences(vector<int> vec, int x);

// count occurrences of 1's in sorted binary array
int countOnes(vector<int> vec);

// find the square root
int squareRoot(int n);

// infinite array => size of array very large (millions) and cannot be used for searching. 
// Unbounded binary-search O(logpos) -> log of position
int findIndexInfiniteArray(vector<int> vec, int x);

// find index of element in a sorted and rotated array
int findIndexSortedRotatedArray(vector<int> vec, int x);

// find the peak element. A peak element is an element which is not smaller than its neighbours
int findPeakElement(vector<int> vec);

// find the pair with sum in an sorted array
std::pair<int, int> findPairWithSum(vector<int> vec, int sum);
vector<int> findPairWithSum(vector<int> vec, int start, int end, int sum);

// find the triplet with sum in an sorted array
vector<int> findTripletWithSum(vector<int> vec, int sum);

// find the median of two sorted arrays
double findMedianTwoSortedArrays(vector<int> vec1, vector<int> vec2);

// TODO: implement these
// count pairs with a given sum
int countPairsWithGivenSum(vector<int> vec, int sum);

// count triplets with a given sum
int countTripletsWithGivenSum(vector<int> vec, int sum);

// find if there is a triplet a,b,c such that a^2 + b^2 = c^2
bool findTripletPythagoras(vector<int> vec);

// find the repeating elements in a array which always satisfies these conditions
// * array is not always sorted
// * array size >= 2 i.e. it always contain a repeated element
// * only one element repeats (any number of times)
// * All the elements from 0 to max(arr) are present. max(arr) is the maxium element value inside array
// * This means then values of elements lie in range 0 <= max(arr) <= n - 2
// If only one repetition {0, 1, 2, 2, 3, 4, 5} => n = 7, max(arr) = 5  (n - 2) 
// if all repetitions     {0, 0, 0, 0, 0, 0, 0} => n = 7, max(arr) = 0  (0)
// the above test shows that 0 <= max(arr) <= (n - 2) --> maximum possible value of max(arr) is
// array size - 2, 1 minus for 0 starting element and 1 minus for one repeated (the least repetition always present). 
int findRepeatingElement(vector<int> vec);

// find the minimum number of pages that must be read by each student
// A student can read only consecutive books and must finish reading a
// book i.e. a book must be read by only single student and cannot be partially read
// Note: if you find minimum for one student, it means some other student
// might have to read more pages.
// So the requirement is to minimize the maximum pages read by each student.
// allocate the minimum number of pages to k students
// Or find the minimum value of the maximum pages read by a student
int findMinimumPagesPerKStudents(vector<int> books, int k); // naive approach
int allocateMinimumPagesPerStudents(vector<int> pages, int k); // binary-search approach


#endif
