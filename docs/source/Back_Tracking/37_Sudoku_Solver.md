# Sudoku Solver
% Hard

## [Problem statement](https://leetcode.com/problems/sudoku-solver/)

Write a program to solve a Sudoku puzzle by filling the empty cells.

A sudoku solution must satisfy all of the following rules:

Each of the digits 1-9 must occur exactly once in each row.
Each of the digits 1-9 must occur exactly once in each column.
Each of the digits 1-9 must occur exactly once in each of the 9 3x3 sub-boxes of the grid.
The '.' character indicates empty cells.

 

### Example 1

![Example 1](37_Sudoku.png)

```plain
Input: board = [["5","3",".",".","7",".",".",".","."],["6",".",".","1","9","5",".",".","."],[".","9","8",".",".",".",".","6","."],["8",".",".",".","6",".",".",".","3"],["4",".",".","8",".","3",".",".","1"],["7",".",".",".","2",".",".",".","6"],[".","6",".",".",".",".","2","8","."],[".",".",".","4","1","9",".",".","5"],[".",".",".",".","8",".",".","7","9"]]

Output: [["5","3","4","6","7","8","9","1","2"],["6","7","2","1","9","5","3","4","8"],["1","9","8","3","4","2","5","6","7"],["8","5","9","7","6","1","4","2","3"],["4","2","6","8","5","3","7","9","1"],["7","1","3","9","2","4","8","5","6"],["9","6","1","5","3","7","2","8","4"],["2","8","7","4","1","9","6","3","5"],["3","4","5","2","8","6","1","7","9"]]

Explanation: The input board is shown above and the only valid solution is shown below:
```

![Solution of Example 1](37_Sudoku_solution.png)

### Constraints

* `board.length == 9`.
* `board[i].length == 9`.
* `board[i][j]` is a digit or `'.'`.
* It is guaranteed that the input board has only one solution.

## Solution

This is a classical example for Back Tracking:

For each empty cell of the `board`, and for each remaining valid digit you need to check if you can go further to other cells with that digit or you have to choose another one to go.

### Code

```cpp
#include <iostream>
#include <vector>

using namespace std;

bool isValid(const vector<vector<char>>& board, int row, int col, char c) {
    // Check row
    for (int i = 0; i < 9; i++) {
        if (board[row][i] == c) return false;
    }
    // Check column
    for (int i = 0; i < 9; i++) {
        if (board[i][col] == c) return false;
    }
    // Check 3x3 sub-box
    for (int i = 0; i < 9; i++) {
        // sub-box's row-position
        auto subrow = 3 * (row / 3) + i / 3;
        // sub-box'scol-position
        auto subcol = 3 * (col / 3) + i % 3;
        if (board[subrow][subcol] == c) return false;
    }
    return true;
}

bool solve(vector<vector<char>>& board) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (board[i][j] == '.') {
                for (char c = '1'; c <= '9'; c++) {
                    if (isValid(board, i, j, c)) {
                        board[i][j] = c;

                        if (solve(board)) {
                            return true;
                        } else {
                            board[i][j] = '.';
                        }
                    }
                }
                return false; // If no valid number can be placed, return false
            }
        }
    }
    return true; // If all cells are filled correctly, return true
}

void solveSudoku(vector<vector<char>>& board) {
    solve(board);
}

void print(const vector<vector<char>>& board) {
    cout << '{';
    for (int i = 0; i < 9; i++) {
        cout << '{';
        for (int j = 0; j < 9; j++) {
            cout << board[i][j];
            if (j < 8) {
                cout << ",";
            }
        }
        cout << "}\n";
    }
    cout << "}\n";
}

int main() {
    vector<vector<char>> board{ {'5','3','.','.','7','.','.','.','.'},
                                {'6','.','.','1','9','5','.','.','.'},
                                {'.','9','8','.','.','.','.','6','.'},
                                {'8','.','.','.','6','.','.','.','3'},
                                {'4','.','.','8','.','3','.','.','1'},
                                {'7','.','.','.','2','.','.','.','6'},
                                {'.','6','.','.','.','.','2','8','.'},
                                {'.','.','.','4','1','9','.','.','5'},
                                {'.','.','.','.','8','.','.','7','9'}};
    solveSudoku(board);
    print(board);
}
```

```plain
Output:
{{5,3,4,6,7,8,9,1,2}
{6,7,2,1,9,5,3,4,8}
{1,9,8,3,4,2,5,6,7}
{8,5,9,7,6,1,4,2,3}
{4,2,6,8,5,3,7,9,1}
{7,1,3,9,2,4,8,5,6}
{9,6,1,5,3,7,2,8,4}
{2,8,7,4,1,9,6,3,5}
{3,4,5,2,8,6,1,7,9}
}
```


### Complexity

* Runtime: `O(9^3)`.
* Extra space: `O(1)`.

## Conclusion

The Sudoku Solver problem is an excellent example of how backtracking can be used to tackle complex problems. 

This approach, where a solution is built incrementally and backtracks when an invalid configuration is encountered, is particularly effective for constraint satisfaction problems like Sudoku. 

The recursive nature of the solution allows for efficient exploration of vast configuration spaces, breaking the problem down into smaller, manageable tasks. 
