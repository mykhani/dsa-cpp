
#include <gtest/gtest.h>
#include <algorithm>
#include <vector>
#include <unordered_set>
#include <numeric>

using namespace std;

/*

Given a multiset of integers, return whether it can be partitioned
into two subsets whose sums are the same.

For example, given the multiset {15, 5, 20, 10, 35, 15, 10},
it would return true, since we can split it up into {15, 5, 10, 15, 10} and {20, 35},
which both add up to 55.

Given the multiset {15, 5, 20, 10, 35},  it would return false,
since we can't split it up into two subsets that add up to the same sum.

Main idea is that if a set can be split into 2, the total sum must be
divisible by 2.

The biggest mistake is trying to use prefix sum assuming that elements
have to be picked in a certain order. THERE IS NO ORDER!

Elements can be picked randomly so sorting the array doesn't help.

One idea is to store all possible permutations of sum in a hash map
and then try to find total_sum/2;

See this nice write-up:
https://leetcode.com/problems/partition-equal-subset-sum/solutions/462699/whiteboard-editorial-all-approaches-explained/

*/

// O(2^n)
bool SplittableIntoSubsetsHashmap(vector<int> &arr)
{

    int n = arr.size();
    int totalSum = std::accumulate(arr.begin(), arr.end(), 0);
    int targetSum = totalSum / 2;

    if (n < 2)
    {
        return false;
    }

    // the total sum cannot be divided into 2
    if (totalSum % 2 != 0)
        return false;

    unordered_set<int> set;
    set.insert(0);

    // O(2^n)
    for (int i = 0; i < arr.size(); i++)
    {
        // insert an element
        for (const auto &s : set)
        {
            set.insert(s + arr[i]); // 1, 2, 4, 8, 16, 32
        }
    }

    return set.find(targetSum) != set.end();
}

/*
                arr = {2, 3, 5}, t = 10/2=5

                    f(5, 0)
        f(5, 1)                  f(3, 1)
  f(5, 2)      f(2, 2)
true       f(2, 3)   skip

*/

// O(2^n)
bool SplittableIntoSubsetsRecursive(vector<int> &arr)
{
    int totalSum = std::accumulate(arr.begin(), arr.end(), 0);
    int targetSum = totalSum / 2;
    int n = arr.size();

    // index is the next potential element to add into the tree
    // it is either add or skipped from the subset
    function<bool(int, int)> findTargetSum = [&](int target, int index) -> bool
    {
        // if index reaches outside array size
        if (index >= arr.size())
            return false;

        // if target has been reached
        if (target == 0)
            return true;

        // two choices, either add index node to the subset or not
        // if index is added to the subset, it is subtracted from the target

        bool result = false;

        // if it is okay to add the current index (backtracking?)
        if (target >= arr[index])
        {
            result = findTargetSum(target - arr[index], index + 1);
        }
        // the OR operator short-circuits so if result is true, no need to go further
        return result || findTargetSum(target, index + 1);
    };

    if (n < 2)
        return false;

    if (totalSum % 2 != 0)
        return false;

    return findTargetSum(targetSum, 0);
}
// See the max-profit-weights problem to learn knapsack solution using
// tabulation. The difference is that capacity is replaced by target sum
// i.e. for subset size represented by i and target sum represented by j,
// a matrix element b[i][j] represents a boolean value that shows if
// the desired target sum j is present within a subset of size i elements
bool SplittableIntoSubsetsKnapsack(vector<int> &arr)
{
    int totalSum = std::accumulate(arr.begin(), arr.end(), 0);
    int targetSum = totalSum / 2; // see above for why

    // early failure
    if (totalSum % 2 != 0)
        return false;

    int n = arr.size(); // max size of the subset
    vector<vector<bool>> b(n + 1, vector<bool>(targetSum + 1, false));

    // base case
    b[0][0] = true; // it is possible to have a set of 0 items with target sum 0

    for (int i = 1; i < b.size(); i++)
    {
        for (int j = 1; j < b[i].size(); j++)
        {
            // check if the target sum j exists with, or without the current element
            int curr_val = arr[i - 1];
            // array bound check
            if (j - curr_val >= 0)
            {
                /*        without              with           */
                b[i][j] = b[i - 1][j] || b[i - 1][j - curr_val];
                // if j - curr_val is true that means the current value
                // makes the target sum. For example if target sum is 5
                // and current value is 3, return true if previous
                // subset contains 5-3=2
            }
            else
            {
                b[i][j] = b[i - 1][j];
            }
        }
    }

    return b[n][targetSum];
}

TEST(SplittableIntoSubsetsHashmap, TestCase1)
{
    vector<int> arr{1, 2, 5};
    EXPECT_EQ(SplittableIntoSubsetsHashmap(arr), false);

    arr = {15, 5, 20, 10, 35, 15, 10};

    EXPECT_EQ(SplittableIntoSubsetsHashmap(arr), true);

    arr = {15, 5, 20, 10, 35};
    EXPECT_EQ(SplittableIntoSubsetsHashmap(arr), false);
}

TEST(SplittableIntoSubsetsRecursive, TestCase1)
{
    vector<int> arr{1, 2, 5};
    EXPECT_EQ(SplittableIntoSubsetsRecursive(arr), false);

    arr = {2, 3, 5};
    EXPECT_EQ(SplittableIntoSubsetsRecursive(arr), true);

    arr = {15, 5, 20, 10, 35, 15, 10};
    // 20, 35 indices: 2, 4

    EXPECT_EQ(SplittableIntoSubsetsRecursive(arr), true);

    arr = {15, 5, 20, 10, 35};
    EXPECT_EQ(SplittableIntoSubsetsRecursive(arr), false);
}

TEST(SplittableIntoSubsetsKnapsack, TestCase1)
{
    vector<int> arr{2, 3, 5};
    EXPECT_EQ(SplittableIntoSubsetsKnapsack(arr), true);

    arr = {1, 2, 5};
    EXPECT_EQ(SplittableIntoSubsetsKnapsack(arr), false);

    arr = {15, 5, 20, 10, 35, 15, 10};
    // 20, 35 indices: 2, 4

    EXPECT_EQ(SplittableIntoSubsetsKnapsack(arr), true);

    arr = {15, 5, 20, 10, 35};
    EXPECT_EQ(SplittableIntoSubsetsKnapsack(arr), false);
}