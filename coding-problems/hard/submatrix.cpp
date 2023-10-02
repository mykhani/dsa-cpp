#include <gtest/gtest.h>
#include <utility>
#include <iostream>

using namespace std;

/*

Let A be an N by M matrix in which every row and every column is sorted.

Given i1, j1, i2, and j2,
compute the number of elements of M smaller than M[i1, j1] and larger than M[i2, j2].

For example, given the following matrix:

[[1, 3, 7, 10, 15, 20],
 [2, 6, 9, 14, 22, 25],
 [3, 8, 10, 15, 25, 30],
 [10, 11, 12, 23, 30, 35],
 [20, 25, 30, 35, 40, 45]]

And i1 = 1, j1 = 1, i2 = 3, j2 = 3, M[i1, j1]=6 and M[i2, j2]=23
return 14 as there are 15 numbers in the matrix smaller than 6 or greater than 23.

*/

// Brute force
int SubMatrixElementsBrute(const vector<vector<int>> &m, const pair<int, int> &p1, const pair<int, int> &p2)
{
    int count = 0;
    const auto &[i1, j1] = p1;
    const auto &[i2, j2] = p2;

    for (int i = 0; i < m.size(); i++)
    {
        for (int j = 0; j < m[i].size(); j++)
        {
            if ((m[i][j] < m[i1][j1]) || (m[i][j] > m[i2][j2]))
                count++;
        }
    }
    return count;
}

// O(n)
int SubMatrixElementsLinear(const vector<vector<int>> &m, const pair<int, int> &p1, const pair<int, int> &p2)
{
    int count = 0;
    const auto &[i1, j1] = p1;
    const auto &[i2, j2] = p2;

    if (m.size() == 0)
    {
        return 0;
    }

    int rows = m.size();
    int cols = m[0].size();

    /* searching for smaller */
    int i = 0, j = cols - 1; // start from top right

    // O(n)
    while (i < rows && j >= 0)
    {
        // check if the element is smaller, if yes, the whole row is valid
        if (m[i][j] < m[i1][j1])
        {
            count += j + 1; // j starts from 0
            // move to lower row with same column
            i++;
        }
        else
        {
            // whole column is greater
            j--;
        }
    }
    // Searching for greater
    // start from top right
    // O(n)
    i = 0;
    j = cols - 1;
    while (i < rows && j >= 0)
    {
        // check if the element is greater, if yes, the whole column is valid
        if (m[i][j] > m[i2][j2])
        {
            count += rows - i; // j starts from 0
            // move to lower row with same column
            j--;
        }
        else
        {
            // whole row is less
            i++;
        }
    }

    return count;
}

TEST(SubMatrixElementsBrute, TestCase1)
{
    vector<vector<int>> m = {{1, 3, 7, 10, 15, 20},
                             {2, 6, 9, 14, 22, 25},
                             {3, 8, 10, 15, 25, 30},
                             {10, 11, 12, 23, 30, 35},
                             {20, 25, 30, 35, 40, 45}};

    EXPECT_EQ(SubMatrixElementsBrute(m, {1, 1}, {3, 3}), 14);
}

TEST(SubMatrixElementsLinear, TestCase1)
{
    vector<vector<int>> m = {{1, 3, 7, 10, 15, 20},
                             {2, 6, 9, 14, 22, 25},
                             {3, 8, 10, 15, 25, 30},
                             {10, 11, 12, 23, 30, 35},
                             {20, 25, 30, 35, 40, 45}};

    EXPECT_EQ(SubMatrixElementsLinear(m, {1, 1}, {3, 3}), 14);
}