# Unique Paths II

## [Problem statement](https://leetcode.com/problems/unique-paths-ii/)

You're given an `m x n` grid represented as an integer array called `grid`. In this grid, there is a robot initially located at the top-left corner (i.e., `grid[0][0]`). The robot's goal is to move to the bottom-right corner (i.e., `grid[m-1][n-1]`). The robot is allowed to move only downwards or to the right at any given point.

The grid contains obstacles and empty spaces, which are marked as `1` or `0` respectively. The robot cannot pass through squares marked as obstacles.

Your task is to determine the number of unique paths the robot can take to reach the bottom-right corner while avoiding obstacles.

It's important to note that the test cases are designed in such a way that the answer will always be less than or equal to `2 * 10^9`. 

### Example 1
![The obstacle grid of Example 1](05_DP_63_robot1.jpg)

```text
Input: obstacleGrid = [[0,0,0],[0,1,0],[0,0,0]]
Output: 2
Explanation: There is one obstacle in the middle of the 3x3 grid above.
There are two ways to reach the bottom-right corner:
1. Right -> Right -> Down -> Down
2. Down -> Down -> Right -> Right
```

### Example 2
![The obstacle grid of Example 2](05_DP_63_robot2.jpg)
```text
Input: obstacleGrid = [[0,1],[0,0]]
Output: 1
``` 

### Constraints

* `m == obstacleGrid.length`.
* `n == obstacleGrid[i].length`.
* `1 <= m, n <= 100`.
* `obstacleGrid[i][j]` is `0` or `1`.

## Solution: Dynamic programming in place

Let us find the relationship between the positions.

If there is no obstacle at the position `(row = i, col = j)`, the number of paths `np[i][j]` that the robot can take to reach this position is:

```text
np[i][j] = np[i - 1][j] + np[i][j - 1]
```

* As long as there is no obstacle in the first row, `np[0][j] = 1`. Otherwise, `np[0][k] = 0` for all `k >= j0`, where `(0, j0)` is the position of the first obstacle in the first row.

* Similarly, as long as there is no obstacle in the first column, `np[i][0] = 1`. Otherwise, `np[k][0] = 0` for all `k >= i0`, where `(i0, 0)` is the position of the first obstacle in the first column.

### Code
```cpp
#include <vector>
#include <iostream>
using namespace std;
int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
    const int row = obstacleGrid.size();
    const int col = obstacleGrid[0].size();
    vector<vector<int>> np(row, vector<int>(col, 0));    
    for (int i = 0; i < row && obstacleGrid[i][0] == 0; i++) {
        np[i][0] = 1;
    }    
    for (int j = 0; j < col && obstacleGrid[0][j] == 0; j++) {
        np[0][j] = 1;
    }
    for (int i = 1; i < row; i++) {
        for (int j = 1; j < col; j++) {
            if (obstacleGrid[i][j] == 0) {
                np[i][j] = np[i - 1][j] + np[i][j - 1];
            }
        }
    }
    return np[row - 1][col - 1]; 
}
int main() {
    vector<vector<int>> obstacleGrid = {{0,0,0},{0,1,0},{0,0,0}};
    cout << uniquePathsWithObstacles(obstacleGrid) << endl;
    obstacleGrid = {{0,1},{0,0}};
    cout << uniquePathsWithObstacles(obstacleGrid) << endl;
}
```
```text
Output:
2
1
```

This solution computes the number of unique paths in an `m x n` grid with obstacles using dynamic programming. It initializes a 2D vector `np` of the same size as `obstacleGrid` to store the number of unique paths for each cell.

First, it initializes the top row and left column of `np`. If there are no obstacles in the top row or left column of `obstacleGrid`, it sets the corresponding cells in `np` to 1 because there's only one way to reach any cell in the top row or left column.

Then, it iterates through the grid starting from the second row and second column (i.e., indices (1, 1)). For each cell, if there's no obstacle (`obstacleGrid[i][j] == 0`), it updates the value in `np` by summing up the values from the cell directly above it and the cell to the left of it. This step efficiently accumulates the number of unique paths while avoiding obstacles.

Finally, the value at `np[row-1][col-1]` contains the total number of unique paths to reach the bottom-right corner of the grid, which is returned as the result.

### Complexity

* Runtime: `O(m*n)`, where `m` and `n` are the dimensions of the grid.
* Extra space: `O(m*n)`.
