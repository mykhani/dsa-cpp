#include "matrix.h"

#include <iostream>

void printMatrix(const vector<vector<int>> &matrix)
{
    int m = matrix.size();
    int n = matrix[0].size();
    
    cout << "Printing matrix: " << endl;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
}

void printMatrixSnakePattern(vector<vector<int>> &matrix)
{
    // 0, 2, 4 
    cout << "Printing matrix in snake pattern: ";
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {
            int offset = matrix[i].size() - 1;
            if (i % 2 == 0)
                cout << matrix[i][j] << " ";
            else 
                cout << matrix[i][offset - j] << " ";
        }
    }
    
    cout << endl;
}

void printMatrixBorder(vector<vector<int>> &matrix)
{
    // assuming row and colums are equal (square matrix?)
    int m = matrix.size();
    int n = matrix[0].size();
    
    cout << "Printing border elements of matrix: "; 
    
    // print top row
    for (int j = 0; j < n; j++) {
        cout << matrix[0][j] << " ";
    }
    
    // print right column
    for (int i = 1; i < m; i++) {
        cout << matrix[i][n - 1] << " ";
    }
    
    // print bottom row
    for (int j = n - 2; m > 1 && j >= 0; j--) {
        cout << matrix[m - 1][j] << " ";
    }
    
    // print left column
    for (int i = m - 2; n > 1 && i > 0; i--) {
        cout << matrix[i][0] << " ";
    }
    
    cout << endl;
}

vector<vector<int>> transposeSquareMatrix(vector<vector<int>> &matrix)
{
    // for each row item, swap with its column
    int m = matrix.size();
    int n = matrix[0].size();
 
    for (int i = 0; i < m; i++) {
        for (int j = i + 1; j < n; j++) {
            // efficient in-place 
            swap(matrix[i][j], matrix[j][i]);
        }
    }
    return matrix;
}

vector<vector<int>> transposeMatrix(vector<vector<int>> &matrix)
{
    // for each row item, swap with its column
    int m = matrix.size();
    int n = matrix[0].size();
 
    if (m == n)
        return transposeSquareMatrix(matrix);
 
    vector<vector<int>> new_matrix(n, vector<int>(m, 0));
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            new_matrix[j][i] = matrix[i][j];    
        }
    }
    
    return new_matrix;
}

vector<vector<int>> rotateMatrix90(vector<vector<int>> &matrix)
{
    int m = matrix.size();
    int n = matrix[0].size();
    
    // first transponse
    for (int i = 0; i < m; i++) {
        for (int j = i + 1; j < n; j++) {
            std::swap(matrix[i][j], matrix[j][i]);
        }
    }
    
    int startRow = 0;
    int endRow =  m - 1;
    
    while (startRow < endRow) {
        for (int j = 0; j < n; j++) {
            std::swap(matrix[startRow][j], matrix[endRow][j]);
        }
        startRow++;
        endRow--;
    }
    
    return matrix;
}

void printMatrixSpiralHelper(vector<vector<int>> &matrix, int top, int right, int bot, int left)
{
    if (left > right || bot < top)
        return;
        
    // print top row
    for (int j = left; j <= right; j++)
        cout << matrix[top][j] << " ";

    // rightmost col
    for (int i = top + 1; i <= bot; i++)
        cout << matrix[i][right] << " ";
        
    // bottom row
    if (top < bot) {
        for (int j = right - 1; j >= left; j--)
            cout << matrix[bot][j] << " ";
    }
    
    if (left < right) {
        // left col
        for (int i = bot - 1; i > top; i--)
            cout << matrix[i][left] << " ";
    }
    
    printMatrixSpiralHelper(matrix, top + 1, right - 1, bot - 1, left + 1);
}

void printMatrixSpiral(vector<vector<int>> &matrix)
{
    int m = matrix.size();
    int n = matrix[0].size();
    
    cout << "Printing matrix in spiral pattern: ";
    printMatrixSpiralHelper(matrix, 0, n - 1, m - 1, 0);
    cout << endl;
}
