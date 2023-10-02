#include <gtest/gtest.h>

using namespace std;

/*
Pascal's triangle is a triangular array of integers
constructed with the following formula:

The first row consists of the number 1. For each subsequent row,
each element is the sum of the numbers directly above it,
on either side. For example, here are the first few rows:

    1
   1 1
  1 2 1
 1 3 3 1
1 4 6 4 1

Given an input k, return the kth row of Pascal's triangle.

Bonus: Can you do this using only O(k) space?
*/

vector<vector<int>> PascalTriangle(int rows)
{
    // Better, more readabile
    vector<vector<int>> result;

    for (int i = 0; i < rows; i++)
    {
        result.push_back(vector<int>(i + 1));
        // make first and last element of row 1
        result[i][0] = 1;
        result[i][i] = 1;

        for (int j = 1; j < i; j++) // due to j = 1, this always happen for second row
        {
            // ignore first and last elements
            result[i][j] = result[i - 1][j] + result[i - 1][j - 1];
        }
    }

    return result;

    // // Original solution
    // vector<vector<int>> result(rows, vector<int>{});
    // vector<int> prev(rows, 0); // previous row
    // vector<int> curr(rows, 0); // current row

    // // rows = 4
    // for (int i = 0; i < rows; i++) // i:0 => i:1   => i:2      => i:3
    // {
    //     for (int j = 0; j <= i; j++) // j:0 => j:0,1 => j:0,1,2  => j:0,1,2,3
    //     {
    //         if (j > 0 && j < i) // boundary elements
    //         {
    //             curr[j] = prev[j] + prev[j - 1];
    //         }
    //         else
    //         {
    //             curr[j] = 1;
    //         }
    //         result[i].push_back(curr[j]);
    //     }
    //     prev = curr;
    // }

    return result;
}

TEST(PascalTriangleBrute, TestCase1)
{
    vector<vector<int>> expected = {
        {1},
        {1, 1},
        {1, 2, 1},
        {1, 3, 3, 1},
        {1, 4, 6, 4, 1},
    };

    EXPECT_EQ(PascalTriangle(5), expected);
}