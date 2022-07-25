#include "searching.h"

#include <iostream>
#include <climits>

template<typename T>
std::ostream& operator<<(std::ostream &os, vector<T> vec) {
	ssize_t size = vec.size();

	os << "[";
	for (int i = 0; i < size; i++) {
		os << vec[i];
		if (i < size - 1)
			os << ", ";
	}

	os << "]" << endl;

	return os;
}

template<>
std::ostream& operator<<(std::ostream &os, vector<bool> vec) {
	ssize_t size = vec.size();

	os << "[";
	for (int i = 0; i < size; i++) {
		os << std::boolalpha << vec[i];
		if (i < size - 1)
			os << ", ";
	}

	os << "]" << endl;

	return os;
}

// using iterative binary search to check if a number x exists in a sorted array
int binarySearchIter(vector<int> vec, int x) {
	// left mid right
	int p = 0;
	int q = vec.size() - 1;
	int r = (p + q) / 2;

	while (p <= q) {
		r = (p + q) / 2;
		if (vec[r] > x) {
			q = r - 1;
		} else if (vec[r] < x) {
			p = r + 1;
		} else {
			return r;
		}
	}

	return -1;
}

//0, 1 , 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17
// Height: ceil(logn) e.g for n = 18, height = 5 
//
//                                                       a8
//                                                 /            \    
//                                              /                 \ 
//                                           /                      \
//                                        /                            \
//                                       a3                             a13
//                                    /      \                        /      \
//                                  /           \                   /          \
//                                a1              a5              a10          a15
//                              /    \          /   \            /   \         /  \
//                            /        \       /     \          /     \       /     \
//                           a0         a2    a4      a6       a9      a11   a14     a16
//                                                   /                    \             \
//                                                 a7                      a12           a17

// using recursive binary search, find the index of number x in a sorted array
int binarySearchRec(vector<int> vec, int x, int p, int q) {
	int r;

//    cout << "Binary search between p: " << p << " and q: " << q << endl;
	if (q < p)
		return -1;

	r = (p + q) / 2;

	if (vec[r] > x)
		return binarySearchRec(vec, x, p, r - 1);
	else if (vec[r] < x)
		return binarySearchRec(vec, x, r + 1, q);
	else
		return r;
}

// find the index of first occuurence
int findIndexFirstOccurrence(vector<int> vec, int x) {
	int p = 0;
	int q = vec.size() - 1;
	int r;
	int result = -1;

	while (p <= q) {
		r = (p + q) / 2;
		if (vec[r] < x) {
			p = r + 1;
		} else if (vec[r] > x) {
			q = r - 1;
		} else {
			result = r;
			q = r - 1;
		}
	}

	return result;
}

// find index of last occurrence
int findIndexLastOccurrence(vector<int> vec, int x) {
	int p = 0;
	int q = vec.size() - 1;
	int r;

	int result = -1;

	while (p <= q) {
		r = (p + q) / 2;
		if (vec[r] > x) {
			q = r - 1;
		} else if (vec[r] > x) {
			p = r + 1;
		} else {
			result = r;
			p = r + 1;
		}
	}

	return result;
}

// count the total occurrences of the number
int findTotalOccurrences(vector<int> vec, int x) {
	int first = findIndexFirstOccurrence(vec, x);

	if (first == -1) {
		return 0;
	}

	int last = findIndexLastOccurrence(vec, x);

	return last - first + 1;
}

// count occurrences of 1's in sorted binary array
int countOnes(vector<int> vec) {
	int first = findIndexFirstOccurrence(vec, 1);

	if (first == -1)
		return 0;

	return vec.size() - first;
}

// find the square root
int squareRoot(int n) {
	// using binary search e.g for n = 25
	// 0, 1, ..... 9
	// 4
	// 2 // 4
	// 3

	int p = 0;
	int q = n;
	int r;
	int result;

	while (p <= q) {
		r = (p + q) / 2;
		if (r * r > n) {
			q = r - 1;
		} else if (r * r < n) {
			result = r;
			p = r + 1;
		} else {
			return r;
		}
	}
	return result;
}

// infinite array => size of array very large (millions) and cannot be used for searching
int findIndexInfiniteArray(vector<int> vec, int x) {
	// search for the index where value is equal to or greater than x
	int i = 1;
	// since we cannot use size, use exception if array bound increased
	try {
		// use .at() for out-of-bound exception
		if (vec.at(0) == x)
			return 0;

		while (vec.at(i) < x) {
			i *= 2;
		}

		if (vec.at(i) == x)
			return i;

		cout << "Found max i: " << i << endl;
		return binarySearchRec(vec, x, i / 2 + 1, i - 1);
	} catch (std::exception &e) {
		std::cout << "Value of i :" << i << endl;
		std::cout << e.what() << endl;
		return binarySearchRec(vec, x, i / 2 + 1, vec.size());
	}
}

// find index of element in a sorted and rotated array
int findIndexSortedRotatedArray(vector<int> vec, int x) {
	//                                          0  1  2  3  4  5   6  7  8  9 10  11  12
	// {5, 6, 7, 8, 9, 10, 1, 2, 3, 4, 5, 5,  5}
	// or {8, 1, 2, 3, 4, 5, 6 ,7}
	// For each point r, there will be a perfectly sorted segment either to its left or right
	// e.g in above, if r is 10, then to its left {5, 6, 7, 8, 9, 10} and towards right {10, 1, 2, 3, 4, 5, 5, 5}
	// if r is 8 then left {5, 6, 7, 8} , right {8, 9, 10, 1, 2, 3, 4, 5, 5, 5}
	// we first search in this perfectly ordered part, and move to next if the number doesn't
	// lie in the segment start and end
	// {5, 4, 3, 2, 1} => search 5

	int p = 0;
	int q = vec.size() - 1;
	int r;
	//        ^
	// {5, 4, 3, 2, 1}
	// {1 ,2, 3, 4, 5}

	while (p <= q) {
		r = (p + q) / 2;
		if (vec[r] == x) {
			return r;
			// find the sorted part
		} else if (vec[r] > vec[p]) {
			// check if the number exists in that range
			if (x >= vec[p] && x < vec[r]) {
				q = r - 1;
				// x doesn't lie in the sorted part, select next
			} else {
				p = r + 1;
			}
			// check the part to the right (might be sorted or not)
		} else {
			// check whether the number lies in this range
			if (x > vec[r] && x <= vec[q]) {
				p = r + 1;
				// the left part might not have been sorted, but might contain the x
			} else {
				q = r - 1;
			}
		}
	}

	return -1;
}

// find the peak element. A peak element is an element which is not smaller than its neighbours (equal is allowed)
int findPeakElement(vector<int> vec) {
	// 1 , 4, 3
//    algo: find midpoint and compare with prev and next elemt
//    if prev < mid and mid > next or corner element:
//        return mid
//    else find next candidate (go left or right?)
//        go towards the higher of the prev and next

	// every independent array has a peak element e.g
	// [10] => peak 10
	// [10, 20] => peak 20
	// [20, 10] => peak 20
	// now if we have an array like {5, 20, 40, 30, 20, 50, 60};
	// the mid is 30. We know 40 is greater than 30. so we ignore {30, 20, 50, 60}
	// and try to find a peak in {5, 20, 40}. If there is other greater element
	// than 40, than that becomes the peak. If 40 is the only element, it is the peak

	int p = 0;
	int q = vec.size() - 1;
	int r;

	while (p <= q) {
		r = (p + q) / 2;
		if ((r == 0 && vec[0] > vec[1])
				|| (r == vec.size() - 1) && vec[r] > vec[r - 1]
				|| vec[r - 1] <= vec[r] && vec[r] >= vec[r + 1]) {
			return vec[r];
		} else if (vec[r - 1] > vec[r]) {
			q = r - 1;
		} else {
			p = r + 1;
		}
	}

	return -1;

}

// find the pair with sum in an sorted array
std::pair<int, int> findPairWithSum(vector<int> vec, int sum) {
	// two pointer approach
	int left = 0;
	int right = vec.size() - 1;
	int curSum;

	while (left < right) {
		curSum = vec[left] + vec[right];

		if (curSum < sum) {
			left++;
		} else if (curSum > sum) {
			right--;
		} else {
			return std::pair<int, int>(vec[left], vec[right]);
		}
	}

	return std::pair<int, int>(-1, -1);
}

vector<int> findPairWithSum(vector<int> vec, int start, int end, int sum) {
	vector<int> result;

	// two pointer approach
	int left = 0;
	int right = vec.size() - 1;
	int curSum;

	while (left < right) {
		curSum = vec[left] + vec[right];

		if (curSum < sum) {
			left++;
		} else if (curSum > sum) {
			right--;
		} else {
			return {vec[left], vec[right]};
		}
	}

	return {-1, -1};
}

// find the triplet with sum in an sorted array
vector<int> findTripletWithSum(vector<int> vec, int sum) {
	vector<int> result = { -1, -1, -1 };
	int n = vec.size() - 1;
	for (int i = 0; i < n; i++) {
		vector<int> pair = findPairWithSum(vec, i + 1, n - 1, sum - vec[i]);
		if (pair != vector<int> { -1, -1 }) {
			result = { vec[i], pair[0], pair[1] };
			break;
		}
	}

	return result;
}

// TODO: implement these
// count pairs with a given sum
int countPairsWithGivenSum(vector<int> vec, int sum) {
	throw std::runtime_error("countPairsWithGivenSum not implemented");
}

// count triplets with a given sum
int countTripletsWithGivenSum(vector<int> vec, int sum) {
	throw std::runtime_error("countTripletsWithGivenSum not implemented");
}

// find if there is a triplet a,b,c such that a^2 + b^2 = c^2
bool findTripletPythagoras(vector<int> vec) {
	throw std::runtime_error("findTripletPythagoras not implemented");
}

// find the median of two sorted arrays. O(n1 + n2)
#if 0
double findMedianTwoSortedArrays(vector<int> vec1, vector<int> vec2)
{
    // combine two sorted arrays first 
    vector<int> combined;

    int i = 0;
    int j = 0;
    
    while (i < vec1.size() && j < vec2.size()) {
        if (vec1[i] < vec2[j]) {
            combined.push_back(vec1[i]);
            i++;
        } else if (vec2[j] < vec1[i]) {
            combined.push_back(vec2[j]);
            j++;
        }
    }
    
    // one of the vector has finished
    while (i < vec1.size()) {
        combined.push_back(vec1[i]);
        i++;
    }
    
    while (j < vec2.size()) {
        combined.push_back(vec2[j]);
        j++;
    }
    
    cout << "Combined array: " << combined << endl;
    
    int n = combined.size();
    
    // if n even: median is (n/2 + n/2 + 1) / 2
    // if n is odd median is n / 2
    return n % 2 != 0 ? combined[n / 2] : 0.5 * (combined[n / 2 - 1] + combined[n/2]);
}
#endif

// find the median of two sorted arrays. O(logn1), make sure vec1 is the smaller (swap if necessary).
// n1 is the size of vec1.
double findMedianTwoSortedArrays(vector<int> vec1, vector<int> vec2) {
	// make sure vec1 is always the smallest
	if (vec1.size() > vec2.size())
		std::swap(vec1, vec2);

	int n1 = vec1.size();
	int n2 = vec2.size();

	int p = 0;
	int q = n1;

	// The goal is to split both vec1 and vec2 into two halves
	// such that left halves of both vec1 and vec2 contains
	// all elements smaller than those in right halves.
	// once that state is achieved, median is calculated as
	// max(left-halves) + min(right-halves) / 2
	while (p <= q) {
		//using binary search, find the middle point in vec1,
		int mid1 = (p + q) / 2;
		// this point divides vec1 into two parts,
		// left-half: from 1 to mid1 - 1 // note: not counting from 0
		// right half: from mid1 to n1 - 1

		// To find the mid point in vec2 such that total number
		// of left half elements is same as right-half elements
		int mid2 = (n1 + n2 + 1) / 2 - mid1;
		// mid2 divides vec2 into
		// left half: 0 to mid2 - 1
		// right half: mid2 to n2 - 1

		int lmax1 = mid1 == 0 ? INT_MIN : vec1[mid1 - 1];
		int rmin1 = mid1 == n1 ? INT_MAX : vec1[mid1];

		int lmax2 = mid2 == 0 ? INT_MIN : vec2[mid2 - 1];
		int rmin2 = mid2 == n2 ? INT_MAX : vec2[mid2];

		// make sure all the element in left halves are smaller than or equal to those in right halves
		if (lmax1 <= rmin2 && lmax2 <= rmin1) {
			if ((n1 + n2) % 2 == 0) {
				return 0.5 * (std::max(lmax1, lmax2) + std::min(rmin1, rmin2));
			} else {
				return std::max(lmax1, lmax2);
			}

			// the midpoint in vec1 needs adjustment, either go left or right
		} else if (lmax1 > rmin2) {
			q = mid1 - 1;
		} else {
			p = mid1 + 1;
		}
	}
}

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
int findRepeatingElement(vector<int> vec) {
	// need to solve it in O(n) time and O(1) space

#if 1    
	// a solution using boolean index table or hash is O(n) time and O(n) space
	vector<bool> visited(vec.size(), false);

	for (int i = 0; i < vec.size(); i++) {
		if (visited[vec[i]] == true) // similar to an element exists in hash. Here index is being used as hash
			return vec[i];

		visited[vec[i]] = true;
	}

	return -1;

#endif

	// O(n) time and O(1) space, using fast and slow pointers and detect
	// a loop
	//             ^-----------^
	// for e.g {1, 2, 3, 4, 5, 2};

	//             ^--------^
	// or      {1, 2, 3, 5, 2, 4};
	// Idea:
	// If we had the array of size n and the values ranged from 1 to n
	// then we could could consider array as a linked list where
	// the value v at index i shows a connection from node i to node v
	// and the head is at index 0
	// e.g array of size 6 {1, 2, 4, 5, 3, 6} could be considered as a SLL
	// 1 -> 2 -> 4 -> 3 -> 5 -> 6 with head = 1

	// Now if there is at least one repetition, more than one node (multiple indices)
	// point to the same node (hold a same value).
	// Also with at least one reptition, the maximum value could be n - 1
	// so the value range from 1 to n - 2 (max).

	// modifying the above array to have a repeated element
	// {1, 2, 4, 5, 3, 5} could be considered as a SLL
	// 1 -> 2 -> 4 -> 3 -> 5 -> 5 i.e. (index/node 3 and 5 both point to 5)

	// Note that in order for this to work, the values must range from 1 to n - 2
	// If it contains 0, then it will get stuck at the first node.
	// So for ranges 0 to n - 2, preprocess the array and add 1 to the values.
	int slow = vec[0] + 1; // head
	int fast = vec[0] + 1; // head

	do {
		slow = vec[slow] + 1;
		fast = vec[vec[fast] + 1] + 1;
	} while (slow != fast);

	slow = vec[0] + 1;
	while (slow != fast) {
		slow = vec[slow] + 1;
		fast = vec[fast] + 1;
	}

	return slow - 1;
}

// start represents the starting index of the subarray in which we find minimum pages
int findMinimumPagesPerKStudentsHelper(vector<int> books, int start, int k) {
	int totalBooks = books.size();

	int result = INT_MAX;

	if (k == 1)
		return std::accumulate(books.begin() + start, books.end(), 0);

	// if only one book left
	if (books.size() - 1 == start) {
		return books[start];
	}

	// Lets say a student reads the first book, it means
	// the rest of the books must be divided among k-1 students
	for (int i = start + 1; i < totalBooks; i++) {
		int readByStudent = std::accumulate(books.begin() + start,
				books.begin() + i, 0);
//		cout << "Pages read by student: " << readByStudent << endl;
		int readByRest = findMinimumPagesPerKStudentsHelper(books, i, k - 1);
//		cout << "Minimum Pages read by the rest: " << readByRest << endl;

		int highestPagesRead = std::max(readByStudent, readByRest);
		result = std::min(highestPagesRead, result);
	}

	return result;
}

int findMinimumPagesPerKStudents(vector<int> books, int k) {
	return findMinimumPagesPerKStudentsHelper(books, 0, k);
}

static int findStudentsRequired(vector<int> pages, int pagesPerStudent) {
    int k = 1;
    int sum = 0;
    for (int i = 0; i < pages.size(); i++) {
        if (sum + pages[i] > pagesPerStudent) {
            k++;
            sum = pages[i];
        } else {
            sum += pages[i];
        }
    }
    return k;
}

// allocate the minimum number of pages to k students
// Or find the minimum value of the maximum pages read by a student
int allocateMinimumPagesPerStudents(vector<int> pages, int k) {
	// in case k = 1, the max possible answer is sum of all pages
	int max = std::accumulate(pages.begin(), pages.end(), 0);
	int min = std::accumulate(pages.begin(), pages.end(), pages[0], [](int& a, int& b) { return std::max(a, b);});

    int possible = min;

    while (min <= max) {
        // find mid which is the possible answer
        int mid = (min + max) / 2;

        auto studentsRequired = findStudentsRequired(pages, mid);
        cout << studentsRequired << " studentsRequired for " << mid << " pages" << endl;
        if (studentsRequired == k) {
            possible = mid;
            max = mid - 1;
        } else if (studentsRequired > k) {
            // increase pages per student
            min = mid + 1;
        } else {
            max = mid - 1;
        }
    }

	return possible;
}
