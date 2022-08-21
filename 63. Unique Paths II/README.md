## 63. Unique Paths II
Tag: dynamic programming

### Problem statement

You are given an `m x n` integer array `grid`. There is a robot initially located at the top-left corner (i.e., `grid[0][0]`). The robot tries to move to the bottom-right corner (i.e., `grid[m-1][n-1]`). The robot can only move either down or right at any point in time.

An obstacle and space are marked as `1` or `0` respectively in `grid`. A path that the robot takes cannot include any square that is an obstacle.

Return the number of possible unique paths that the robot can take to reach the bottom-right corner.

The test cases are generated so that the answer will be less than or equal to `2 * 10^9`.

 

#### Example 1
![Example 1](63_robot1.jpg)

```plain
Input: obstacleGrid = [[0,0,0],[0,1,0],[0,0,0]]
Output: 2
Explanation: There is one obstacle in the middle of the 3x3 grid above.
There are two ways to reach the bottom-right corner:
1. Right -> Right -> Down -> Down
2. Down -> Down -> Right -> Right
```

#### Example 2
![Example 2](63_robot2.jpg)
```plain
Input: obstacleGrid = [[0,1],[0,0]]
Output: 1
``` 

#### Constraints

* `m == obstacleGrid.length`.
* `n == obstacleGrid[i].length`.
* `1 <= m, n <= 100`.
* `obstacleGrid[i][j]` is `0` or `1`.

### Solution: Dynamic programming in place

Let us find the relationship between the positions.

If there is no obstacle at position `(row = i, col = j)`, the number of paths `np[i][j]` that the robot can take to reach this position is:

```plain
np[i][j] = np[i - 1][j] + np[i][j - 1]
```

* As long as there is no obstacle in the first row, `np[0][j] = 1`. Otherwise, `np[0][k] = 0` for all `k >= j0`, where `(0, j0)` is the position of the first obstacle in the first row.

* Similarly, as long as there is no obstacle in the first column, `np[i][0] = 1`. Otherwise, `np[k][0] = 0` for all `k >= i0`, where `(i0, 0)` is the position of the first obstacle in the first column.

#### Code
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
```plain
Output:
2
1
```

#### Complexity
* Runtime: `O(m*n)`, where `m x n` is the size of the `grid`.
* Extra space: `O(m*n)`.

### References
* [(https://leetcode.com/problems/unique-paths-ii/)](https://leetcode.com/problems/unique-paths-ii/)
* [https://www.leetsolve.com/63-unique-paths-ii](https://www.leetsolve.com/63-unique-paths-ii)