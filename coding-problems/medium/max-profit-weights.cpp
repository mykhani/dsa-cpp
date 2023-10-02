#include <gtest/gtest.h>
#include <unordered_map>

using namespace std;

/*

Given N items where each item has some weight and profit associated with it
and also given a bag with capacity W, [i.e., the bag can hold at most W weight in it].
The task is to put the items into the bag such that the sum of profits associated
with them is the maximum possible.

Input: capacity = 4, profit[] = {1, 2, 3}, weight[] = {4, 5, 1}

 */

int MaxProfitWeightsRecursive(vector<int> profits, vector<int> weights, int capacity)
{
    // create all the subsets of weights (permutations) and maintain max profit
    function<int(int, int)> maxProfit = [&](int W, int index) -> int
    {
        int profit = 0;

        if (index >= weights.size() || W <= 0)
        {
            return 0;
        }
        bool result = false;

        // either add index or skip it
        if (capacity >= weights[index])
        {
            profit = profits[index] + maxProfit(capacity - weights[index], index + 1);
        }
        // return max of profit with this index and without it
        return std::max(profit, maxProfit(capacity, index + 1));
    };

    return maxProfit(capacity, 0);
}

/*

For weight[] = {1, 1, 1}, capacity = 2, profit[] = {10, 20, 30}
the recursion tree looks like
                                mp(2, 0)
                             /           \-----------------------\
                    mp(2, 1)                                       mp(1, 1)
                /             \                                /               \
          mp(2, 2)              mp(1, 2)                 mp(1, 2)                mp(0, 2)
          /    \               /        \              /         \
    mp(2, 3)    mp(1, 3)   mp(1, 3)     mp(0, 3)     mp(1, 3)     mp(0, 3)

There are multiple repeated recursive calls e.g. mp(1, 2)
So we can use memoization

Intuitively if you look at two subsets, one without w0 (weight[0]) and other with it i.e
 w1, w2 and w0, w1, w2 (which represents two branches of the tree), You can see that
 calculation for subset w1, w2 is common. Ofcourse this happens if all weights are equal.
*/

struct pair_hash
{
    template <typename T1, typename T2>
    std::size_t operator()(const std::pair<T1, T2> &p) const
    {
        return std::hash<T1>()(p.first) ^ std::hash<T2>()(p.second);
    }
};

// Above recursive solution with memoization
/*
From: https://www.geeksforgeeks.org/0-1-knapsack-problem-dp-10/
Time Complexity: O(N * W). As redundant calculations of states are avoided.
Auxiliary Space: O(N * W) + O(N). The use of a 2D array data structure for
storing intermediate states and O(N) auxiliary stack space(ASS) has been used
for recursion stack

See what is the effect of memoization on time complexity and auxillary space
when using hashmap?
*/
int MaxProfitWeightsMemo(vector<int> profits, vector<int> weights, int capacity)
{
    // matrix memo for capacity and index combinations
    // vector<vector<int>> memo(capacity + 1, vector<int>(weights.size(), -1));

    // NOTE: memo can be a hashmap of pair(capacity, index) for quick lookup
    unordered_map<pair<int, int>, int, pair_hash> memo;

    // create all the subsets of weights (permutations) and maintain max profit
    function<int(int, int)> maxProfit = [&](int W, int index) -> int
    {
        int profit = 0;

        if (index >= weights.size() || W <= 0)
        {
            return 0;
        }
        bool result = false;

        // if (memo[W][index] == -1)
        if (memo.find({W, index}) == memo.end())
        {
            // either add index or skip it
            if (capacity >= weights[index])
            {
                profit = profits[index] + maxProfit(capacity - weights[index], index + 1);
            }
            // return max of profit with this index and without it
            memo[{W, index}] = std::max(profit, maxProfit(capacity, index + 1));
        }
        return memo[{W, index}];
    };

    return maxProfit(capacity, 0);
}
/*
Tabulation

let w={1, 2, 3}, p={10, 15, 40}, capacity=6

Create a matrix where each cell m[i][j] represents max profit
with i elements and j capacity (or capacity remaining).

To find the max profit for certain subset consisting of i elements and j
remaining capacity, the formula is
max profit of i elements = MAX(max profit of i elements with current element excluded,
                               max profit of i elements with current element included
or
max[i][j] = std::max(max[i-1][j], p[i-1] + max[i-1][j - w[i-1]])


         +-----+-----+-----+-----+-----+-----+-----+
         |  0  |  1  |  2  |  3  |  4  |  5  |  6  |  --> available capacity (in chunks of 1)
   +-----+-----+-----+-----+-----+-----+-----+-----+
   |  0  |  0  |  0  |  0  |  0  |  0  |  0  |  0  | profit is 0 for 0 items in bag with 0 capacity
   +-----+-----+-----+-----+-----+-----+-----+-----+
   |  1  |  0  |  10 |  10 | 10  | 10  | 10  | 10  | Note that m[1][2] = 10 because even though capacity is 2, we can put only 1 item in the bag for this row
   +-----+-----+-----+-----+-----+-----+-----+-----+
   |  2  |  0  |  10 |  15 | 25  | 25  | 25  | 25  |
   +-----+-----+-----+-----+-----+-----+-----+-----+
   |  3  |  0  |  10 |  15 | 40  |  50 | 55  |  65 | m[3][4] = std::max(m[2][4], 40 + m[2][4-3]) = max(25, 50)=50
   +-----+-----+-----+-----+-----+-----+-----+-----+
      ^
number of items

*/

// DP Bottom up approach, iterative
// O(N * capacity) where N is size of items array i.e. weights.size() or profits.size()
int MaxProfitWeightsTabulation(vector<int> profits, vector<int> weights, int capacity)
{
    // rows = n items
    int n = weights.size();                                     // same as profits.size()
    vector<vector<int>> m(n + 1, vector<int>(capacity + 1, 0)); // n + 1 because 1 row for 0 elements in bag

    for (int i = 1; i < m.size(); i++)
    { // rows
        for (int j = 1; j < m[i].size(); j++)
        {
            int curr_p = profits[i - 1];
            int curr_w = weights[i - 1];
            // j - curr_w could result in negative index so check that
            // to avoid array index out of bounds failure
            if (j - curr_w >= 0)
            {
                m[i][j] = std::max(m[i - 1][j], curr_p + m[i - 1][j - curr_w]);
            }
            else
            {
                // no capacity for the current item/weight, use previous value
                m[i][j] = m[i - 1][j];
            }
        }
    }

    return m[n][capacity];
}

TEST(MaxProfitWeightsRecursive, TestCase1)
{
    vector<int> w{4, 5, 1};
    vector<int> p{1, 2, 3};

    EXPECT_EQ(MaxProfitWeightsRecursive(p, w, 4), 3);
}

TEST(MaxProfitWeightsMemo, TestCase1)
{
    vector<int> w{4, 5, 1};
    vector<int> p{1, 2, 3};

    EXPECT_EQ(MaxProfitWeightsMemo(p, w, 4), 3);
}

TEST(MaxProfitWeightsTabulation, TestCase1)
{
    vector<int> w{4, 5, 1};
    vector<int> p{1, 2, 3};

    EXPECT_EQ(MaxProfitWeightsTabulation(p, w, 4), 3);
}