#include <vector>
#include <gtest/gtest.h>

using namespace std;

/*
 Given a matrix M of n*n size, the task is to complete
 the function which prints its elements in a diagonal
 pattern as depicted below.

 M={
    1, 2, 3,
    4, 5, 6,
    7, 8, 9
 }

 1 - 2  3
   /  / |
 4  5   6
 | /  /
 7  8 - 9


00, 01, 10, 20, 11, 02, 12, 21, 22
 Output:
 1 2 4 7 5 3 6 8 9

M={
    1 , 2 , 3 , 4
    5 , 6 , 7 , 8
    9 , 10, 11, 12
    13, 14, 15, 16
 }

 1 - 2   3 - 4
   /   /   /
 5   6   7   8
 | /   /   / |
 9   10  11  12
   /   /   /
 13 -14  15 -16


Output:
1, 2, 5, 9, 6, 3, 4, 7, 10, 13, 14, 11, 8, 12, 15, 16


*/

vector<int> MatrixDiagonally(vector<vector<int>> m)
{
    vector<int> result;
    bool upwards = true;
    int n = m.size(); // it is a square matrix
    int remaining = n * n;
    int i = 0;
    int j = 0;
    while (remaining > 0)
    {
        // up-right
        if (upwards)
        {
            if (i >= 0 && j < n)
            {
                result.push_back(m[i][j]);
                remaining--;
                // go up-right
                i--;
                j++;
            }
            else if (i < 0 && j < n)
            {
                // go right
                i = 0;
                // j++;
                upwards = false;
            }
            else if (j == n)
            {
                // go down
                j--;
                i += 2;
                upwards = false;
            }
        }
        else
        {
            if (j >= 0 && i < n)
            {
                // left right
                result.push_back(m[i][j]);
                remaining--;
                i++;
                j--;
            }
            else if (j < 0 && i < n)
            {
                // go down
                j = 0;
                // i++;
                upwards = true;
            }
            else if (i == n)
            {
                // go right
                i--;
                j += 2;
                upwards = true;
            }
        }
    }
    return result;
}

TEST(MatrixDiagonally, TestCase1)
{
    vector<vector<int>> m = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}};

    vector<int> result = MatrixDiagonally(m);
    vector<int> expected{1, 2, 4, 7, 5, 3, 6, 8, 9};
    EXPECT_EQ(result, expected);

    m = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}};
    result = MatrixDiagonally(m);
    expected = {1, 2, 5, 9, 6, 3, 4, 7, 10, 13, 14, 11, 8, 12, 15, 16};
    EXPECT_EQ(result, expected);
}