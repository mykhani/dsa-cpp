#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

using namespace std;
/*
 * In a 2-dimension matrix in C++, the elements are stored in a row major order
 * e.g 
 * int matrix[3][3] = {
 *     {1, 2, 3},
 *     {4, 5, 6},
 *     {7, 8, 9}
 * };
 * Elements are stored as 1, 2, 3, 4, 5, 6, 7, 8, 9 at consecutive memory addresses i.e. row-wise
 * if it were column major, it would have stored elements as
 * 1, 4, 7, 2, 5, 8, 3, 6, 9 at consecutive memory addresses
 * 
 * The curly braces are optional
 * 
 * only the first dimension can be omitted when initializing the matrix
 * int matrix[][3] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
 * 
 * From C++14 standard, variable arrays are allowed e.g.
 * int m = 3, n = 3
 * int matrix[m][n] = ...
 * 
 * Creating matrix on heap
 * int m = 3, n = 3;
 * int **matrix;
 * matrix = new int*[m];
 * for (int i = 0; i < m; i++) {
 *     matrix[i] = new int[n];
 * }
 * 
 * Disadvantage of dynamically allocated matrix, not cache-friendly
 * The rows could not be in contiguous memory region.
 * 
 * Matrix using vector
 * int m = 3;
 * vector<int> matrix[m]; array of 3 vector<int>, m is rows
 * 
 * or
 * int m = 3, n = 3;
 * vector<vector<int>> matrix;
 * 
 * ADVANTAGE: number of rows and columns can be dynamic
 * 
 * for (int i = 0; i < m; i++) {
 *     vector<int> row;
 *     for (int j = 0; j < n; j++) {
 *         row.push_back(j);
 *     }
 *     matrix.push_back(row);
 * }
 * 
 * Passing matrix to a function (a general function that can take any number of rows and columns
 * void function(int **matrix, int m. int n);
 * void function(int *matrix[], int m. int n);
 * void function(vector<int> row[], int m); // no need to pass n as n = row.size()
 * void function(vector<vector<int>> matrix[]); // m = matrix.size(), n = matrix[i].size()
 */
 void printMatrix(const vector<vector<int>> &matrix);
 // Time: O(mxn), space O(1)
 void printMatrixSnakePattern(vector<vector<int>> &matrix);
 // Time: O(m + n)
 void printMatrixBorder(vector<vector<int>> &matrix);
 
 vector<vector<int>> rotateMatrix90(vector<vector<int>> &matrix);
 
 // Time: O(n^2), space: O(1)
 vector<vector<int>> transposeMatrix(vector<vector<int>> &matrix);
 
 void printMatrixSpiral(vector<vector<int>> &matrix); 
#endif