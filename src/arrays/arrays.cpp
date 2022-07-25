#include "arrays.h"

#include <unordered_set>
#include <unordered_map>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <numeric>

using namespace std;

template <typename T>
std::ostream& operator<<(std::ostream& os, vector<T> vec)
{
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

std::ostream& operator<<(std::ostream& os, std::unordered_map<int, int>& map)
{
    
    os << "[";
    for (auto&& e : map) {
        os << "(" << e.first << ", " << e.second << "), ";
        
    }
    
    os << "]" << endl;

    return os;
}

// Time complexity of comparisons
// if n is even 1 + 3*(n-2 /2) = 1 + 1.5n -3 = 1.5n - 2
// if n is odd: 1 + 3*(n-2 /2) + 3 = 1 + 1.5n - 4.5 + 3 =  1.5n + 0.5 ~ 1.5n
pair<int , int> findMinMax(vector<int> arr) {
	int n = arr.size();
    int min = arr[0];
    int max = arr[0];

    if (arr[0] < arr[1]) {
        min = arr[0];
        max = arr[1];
    } else {
        min = arr[1];
        max = arr[0];
    }

    // check in pairs, a new pair is either (max, min) or (min, max) or neither
    // in other words, the greater of the new pair could be a new max or
    // the smaller of the new pair could be a new minimum or neither of above
    for (int i = 2; i < n - 2; i += 2) {
        // total 3 comparisons

        if (arr[i] < arr[i + 1]) { // one comparison
            max = std::max(max, arr[i + 1]); // one comparison
            min = std::min(min, arr[i]); // one comparison
        } else {
            max = std::max(max, arr[i]); // one comparison
            min = std::min(max, arr[i+1]); // one comparison
        }
    }

    // for odd length arrays
    if (n % 2) { // one comparison
        max = std::max(max, arr[n-1]); // one comparison
        min = std::min(min, arr[n-1]); // one comparison
    }

    return {min, max};
}

// find the largest integer
int largest(vector<int> vec)
{
    if (vec.size() == 0)
        return -1;
        
    int result = vec[0];
    
    for (int i = 1; i < vec.size(); i++) {
        result = std::max(result, vec[i]);
    }
    
    return result;
}

// find the index of the largest integer
int largestIndex(vector<int> vec)
{
    if (vec.size() == 0)
        return -1;
        
    int result = 0;
    
    for (int i = 1; i < vec.size(); i++) {
        if (vec[i] > vec[result])
            result = i;
    }
    
    return result;
}

// find second largest integer
int secondLargest(vector<int> vec)
{
    int result = -1;
    
    if (vec.size() == 0)
        return -1;
        
    int max = vec[0];
    
    for (int i = 1; i < vec.size(); i++) {
        if (vec[i] > max) {
            result = max;
            max = vec[i];
        } else if (vec[i] != max) {
            if (result == -1 || vec[i] > vec[result]) {
                result = vec[i];
            }
        }
    }
    
    return result;
}

// find second largest integer index
int secondLargestIndex(vector<int> vec)
{
    int result = -1;
    
    if (vec.size() == 0)
        return -1;
        
    int maxIndex = 0;
    
    for (int i = 1; i < vec.size(); i++) {
        if (vec[i] > vec[maxIndex]) {
            result = maxIndex;
            maxIndex = i;
        } else if (vec[i] != vec[maxIndex]) {
            if (result == -1 || vec[i] > vec[result])
                result = i;
        }
    }
    
    return result;
}

// check if an array is sorted in increasing or descending order
bool isSorted(vector<int> vec, bool ascending)
{
    for (int i = 1; i < vec.size(); i++) {
        // if ascending order, the consecutive element should be greater
        if (ascending && vec[i] < vec[i - 1])
            return false;
        if (!ascending && vec[i] > vec[i - 1])
            return false;
    }
    
    return true;
}

// reverse an array.
vector<int> reverse(vector<int>& vec)
{
    int i = 0;
    int j = vec.size() - 1;
    
    for (; i < j; i++, j--) {
        swap(vec[i], vec[j]);
    }
    
    return vec;
}

// reverse part of the array from begin to end.
vector<int> reverse(vector<int>&vec, int begin, int end)
{
    int i = begin;
    int j = end;
    
    for (; i < j; i++, j--) {
        swap(vec[i], vec[j]);
    }
    
    return vec;
}

// remove duplicates from an array. Works for unsorted arrays
vector<int> removeDuplicates(vector<int> vec)
{
    vector<int> result;
    std::unordered_set<int> set;
    
    for (int i = 0; i < vec.size(); i++) { // O(n)
        // element not found in set
        if (set.find(vec[i]) == set.end()) { // O(1)
            set.insert(vec[i]);  // O(1)
            result.push_back(vec[i]);
        }
    }
    
    return result;
}

// move zeroes to end O(n)
vector<int> moveZeroesToEnd(vector<int> vec)
{
    int nonZeroIndex = 0;
    
    for (int i = 0; i < vec.size(); i++) {
        if (vec[i] != 0) {
            if(i != nonZeroIndex) {
                cout << "swapping " << vec[nonZeroIndex] << " with " << vec[i] << endl;
                swap(vec[nonZeroIndex], vec[i]);
            }
            nonZeroIndex++;
        }
    }
    
    return vec;
}

// rotate an array left by one place
vector<int> leftRotateByOne(vector<int> vec)
{
    int leftMost = vec[0];
    int n = vec.size();
    
    for (int i = 0; i < n - 1; i++) {
        vec[i] = vec[i + 1];
    }
    
    vec[n - 1] = leftMost;
    
    return vec;
}

vector<int> leftRotate(vector<int> vec, int k)
{
    // {1, 2, 3, 4, 5} left 3
    // {4, 5, 1, 2, 3} //
    // 3, 2, 1, 5, 4
    // 4, 5, 1, 2, 3
    // reverse 0 to k - 1
    // reverse k to n - 1
    // reverse 0 to n - 1
    
    // if k > vec.size(), use module as 
    // left rotate by vec.size() is equal to original array e.g.
    // leftRotate({1, 2, 3, 4, 5}, 5) returns {1, 2, 3 ,4, 5} i.e. the 
    // original array
    
    k = k % vec.size();
    
    if (k = 0)
        return vec;
    
    reverse(vec, 0, k - 1);
    reverse(vec, k, vec.size() - 1);
    reverse(vec, 0, vec.size() - 1);
    
    return vec;
}

// find leaders in an array. A leader is an element with no greater element to its right
vector<int> leaders(vector<int> vec)
{
    // start from right, rightmost is always leader
    vector<int> result;
    
    int size = vec.size();
    int maxRight = vec[size - 1]; // rightmost maximum
    
    result.push_back(maxRight);
    
    for (int i = size - 2; i >= 0; i--) {
        if (vec[i] > maxRight) {
            result.push_back(vec[i]);
            maxRight = vec[i];
        }
    }
    
    return result;
}

// find the maximum difference vec[j] - vec[i] such that j > i
int maxDifference(vector<int> vec)
{
    // algo
    // the diff is max if the left value is the smallest
    // so we traverse the vector, keep track of the smallest
    // left value and find the max diff for each element
    if (vec.size() < 2) {
        return -1;
    }
    
    int minLeft = vec[0];
    int maxDiff = vec[1] - minLeft;
    
  
    
    for (int i = 2; i < vec.size(); i++) {
        minLeft = std::min(minLeft, vec[i - 1]);
        int diff = vec[i] - minLeft;
        maxDiff = std::max(diff, maxDiff);
    }
    
    return maxDiff;
}

// find the frequencies of elements in a sorted array
vector<std::pair<int, int>> frequenciesSorted(vector<int> vec)
{
    // array is sorted, it means if there are multiple same integers,
    // they occur consecutively
    // {10, 20, 20, 30, 30, 30, 40, 40, 40, 40};
    
    vector<std::pair<int, int>> results;
    int curr= vec[0];
    int count = 1;
    
    for (int i = 1; i < vec.size(); i++) {
        if (vec[i] == curr) {
            count++;
        } else {
            results.push_back(std::pair<int, int>(curr, count));
            count = 1;
            curr = vec[i];
        }
    }
    
    // last element
    results.push_back(std::pair<int, int>(curr, count));
    
    return results;
}

// find the maximum profit in stocks
int maxProfitStocks(vector<int> vec)
{
    // max profit => add the rises
    int profit = 0;
    for (int i = 1; i < vec.size(); i++) {
        int diff = vec[i] - vec[i - 1];
        if (diff > 0) {
            profit += diff;
        }
    }
    
    return profit;
}

// find the trapped rain water
int trappedRainWater(vector<int> vec)
{
    // {2, 0, 2}
    // for each height, maintain max to its left and right
    int n = vec.size();
    
    vector<int> lmax(n, 0);
    vector<int> rmax(n, 0);
    
    lmax[0] = vec[0];
    rmax[0] = vec[0];
    
    for (int i = 1; i < vec.size() - 1; i++) {
        lmax[i] = std::max(vec[i], lmax[i - 1]);
    }
    
    lmax[n - 1] = vec[n - 1];
    rmax[n - 1] = vec[n - 1];
    
    for (int i = n - 2; i > 0; i--) {
        rmax[i] = std::max(vec[i], rmax[i + 1]);
    }
    
    cout << "Left max: " << lmax << endl;
    cout << "Right max: " << rmax << endl;
    
    int trapped = 0;
    for (int i = 0; i < n; i++) {
        trapped += (std::min(lmax[i], rmax[i]) - vec[i]);
    }
    
    return trapped;
}

// maximum consecutive 1's in a binary array
int maxConsecutiveOnes(vector<int> vec)
{
    // {1, 1, 0, 0, 1, 1, 1, 1}
    // if element is 1, increment count
    // if element is 0, reset count
    
    
    int maxCount = 0;
    int currCount = 0;
    
    for (int i = 0; i < vec.size(); i++) {
        if (vec[i] == 0) {
            currCount = 0;
        } else {
            currCount++;
        }
        
        maxCount = std::max(maxCount, currCount);
    }
    
    return maxCount;
}

// int maximum sub array sum (kadane's algorithm)
int maxSubarraySum(vector<int> vec)
{
    int maxSum = vec[0];
    int currSum = vec[0];
    
    for (int i = 1; i < vec.size(); i++) {
        if (currSum + vec[i] > vec[i]) {
            currSum += vec[i];
        } else {
            currSum = vec[i];
        }
        maxSum = std::max(currSum, maxSum);
    }
    
    return maxSum;
}

// maximum length even-odd array
int maxEvenOddArray(vector<int> vec)
{
    int maxLen = 1;
    int count = 1;
    
    for (int i = 1; i < vec.size(); i++) {
        // previous even and current odd or
        // previous odd and current even
        if (
            vec[i - 1] % 2 == 0 && vec[i] % 2 != 0 ||
            vec[i - 1] % 2 != 0 && vec[i] % 2 == 0
        ) {
            count++;
        } else {
            count = 1;
        }
        maxLen = std::max(count, maxLen);
    }
    
    return maxLen;
}

// find the maximum circular subarray sum
int maxCircularSubarraySum(vector<int> vec)
{
    int totalSum = std::accumulate(vec.begin(), vec.end(), 0);
    
    int maxLinearSum = maxSubarraySum(vec);
    
    vector<int> negVec(vec.size());
    
    std::transform(vec.begin(), vec.end(), negVec.begin(), [](int x) {
        return -x;
    });
    
    int minSum = maxSubarraySum(negVec);
    int maxCircularSum = totalSum + minSum;
    
    return std::max(maxCircularSum, maxLinearSum);
}

// a majority element is an element, that appears more than n / 2 times in an array
int findMajorityElement(vector<int> vec)
{
    // voting algorithm
    int candidate = 0;
    int count = 1;
    
    for (int i = 1; i < vec.size(); i++) {
        if (vec[i] == vec[candidate]) {
            count++;
        } else {
            count--;
            if (count == 0) {
                candidate = i;
                count = 1;
            }
        }
    }
    
    count = 0;
    
    for (int i = 0; i < vec.size(); i++) {
        if (vec[i] == vec[candidate]) {
            count++;
        }
    }
    
    return count > (vec.size() / 2) ? candidate : -1;
}

// find the maxium sum of k cosecutive elements
int maxSumKConsecutive(vector<int> vec, int k)
{
    int currSum = 0;
    int maxSum = 0;
    
    for (int i = 0; i < vec.size(); i++) {
        if (i >= k) {
            currSum -= vec[i - k];
        }
        
        currSum += vec[i];
        maxSum = std::max(currSum, maxSum);
    }
    
    return maxSum;
}

// check if a subarray with the given sum exists. Works if array contains only positive numbers O(n) time, O(1) space
bool subarrayWithSum(vector<int> vec, int targetSum)
{
    // {1, 5, 20, 10, 3, 11}, let say sum = 33
    int left = 0;
    int right = 0;
    int currSum = 0;
    
    while (right < vec.size()) {
        if (currSum < targetSum) {
            currSum += vec[right];
            right++;
        } else if (currSum > targetSum) {
            currSum -= vec[left];
            left++;
        } else {
            return true;
        }
    }
    
    return false;
}

// compute k n-bonnaci numbers
vector<int> computeKNBonnaci(int n, int k)
{
    // fibonnaci -> 2-bonnaci
    // 0, 1, 1, 2
    vector<int> result(k, 0);
    
    result[n - 1] = 1;
    
    int currSum = 0;
    
    for (int i = 0; i < n; i++) {
        currSum += result[i];
    }
    
    for (int i = n; i < k; i++) {
        result[i] = currSum;
        currSum += (result[i] - result[i - n]);
    }
    
    return result;
}

// find distinct elements in window of size k
vector<int> distinctElementsWindowSizeK(vector<int> vec, int k)
{
    vector<int> result;
    std::unordered_map<int, int> counter;
    
    for (int i = 0; i < vec.size(); i++) {
        counter[vec[i]]++;
        if (i >= k - 1) {
            cout << "Counter " << counter << endl;
            result.push_back(counter.size());
            counter[vec[i - k + 1]]--;
            if (counter[vec[i - k + 1]] == 0)
                counter.erase(vec[i - k + 1]);
            
        }
    }
    
    return result;
}

vector<std::pair<int, int>> miniumGroupFlips(vector<int> vec)
{
    vector<std::pair<int, int>> result;
    
    // 1, 0, 0, 1, 1, 1, 0
    // flip the second group if it exists
    int first = vec[0];
    
    int left = 0;
    int right = 0;
    
    for (int i = 1; i < vec.size(); i++) {
        if (vec[i] != vec[i - 1]) {
            if (vec[i] != first) {
                left = i;
            } else {
                right = i - 1;
                result.push_back(std::pair<int, int>(left, right));
            }
        }
    }
    
    if (left > right) {
        result.push_back(std::pair<int, int>(left, vec.size() - 1));
    }
    
    return result;
}

// get sum of elements between start and end
int getSum(vector<int> vec, int start, int end)
{
    vector<int> prefixSum(vec.size(), 0);
    
    prefixSum[0] = vec[0];
    
    for (int i = 1; i < vec.size(); i++) {
        prefixSum[i] = vec[i] + prefixSum[i - 1];
    }
    
    if (start == 0) {
        return prefixSum[end];
    }
    
    return prefixSum[end] - prefixSum[start - 1];
}

// see if equilibrium point exists. Equilibrium point is an element whose left and right sum is equal
std::pair<bool, int> equilibriumExisits(vector<int> vec)
{
    // check corner cases
    // first element
    int n = vec.size();
    int totalSum = std::accumulate(vec.begin(), vec.end(), 0);
    
    int currSum = 0;
    
    for (int i = 0; i < vec.size() - 1; i++) {
        if (currSum == totalSum - vec[i]) {
            return std::pair<bool, int>(true, i);
        }
        currSum += vec[i];
        totalSum -= vec[i];
    }
    
    return std::pair<bool, int>(false, -1);
}

// find the maximum occurring element within ranges
int maxOccuringInRanges(vector<int> left, vector<int> right)
{
    // find the maximum number in ranges
    int max = right[0];
    for (int i = 1; i < right.size(); i++) {
        max = ::max(right[i], max);
    }
    
    vector<int> lookup(max + 1, 0); // {0, 1, 2, 3, 4, 5, 6,...max}
    
    for (int i = 0; i < left.size(); i++) {
        lookup[left[i]]++;
        lookup[right[i] + 1]--;
    }
    
    vector<int> prefixSum(lookup.size(), 0);
   
    prefixSum[0] = lookup[0];
    max = 0;
 
    for (int i = 1; i < prefixSum.size(); i++) {
        prefixSum[i] = lookup[i] + prefixSum[i - 1];
        if (prefixSum[i] > prefixSum[max])
            max = i;
    }
    
    return max;
}

// check if a given array can be divided into three parts with equal sum
bool divisibleThreePartsWithEqualSum(vector<int> vec)
{
    throw std::runtime_error("Function not implemented");
}

// check if a given array contains a subarray with 0 sum
bool containsSubarrayWithZeroSum(vector<int> vec)
{
    throw std::runtime_error("Function not implemented");
}

// find the longest subarray with equal number of 0's and 1's with a binary array
int longestSubarrayWithEqualOnesZeroes(vector<int> vec)
{
    throw std::runtime_error("Function not implemented");
}

// remove an element from vector (like std::remove)
vector<int>::iterator Remove(vector<int>::iterator begin, vector<int>::iterator end, int match) {
    auto curr = begin;
    auto unique = begin;

    while (curr != end) {
        if (*curr != match) {
            *unique = *curr;
            unique++;
        }

        curr++;
    }

    return unique;
}
