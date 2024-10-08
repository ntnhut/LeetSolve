# Unique Paths
% Medium https://leetcode.com/problems/unique-paths/
## [Problem statement](https://leetcode.com/problems/unique-paths/)

A robot starts at the top-left corner of a grid with dimensions `m x n`. It can move either down or right at each step. The robot's goal is to reach the bottom-right corner of the grid.

The problem is to determine the number of unique paths the robot can take to reach the bottom-right corner.

### Example 1

![The grid of Example 1](62_robot_maze.png)

```text
Input: m = 3, n = 7
Output: 28
```

### Example 2

```text
Input: m = 3, n = 2
Output: 3
Explanation:
From the top-left corner, there are a total of 3 ways to reach the bottom-right corner:
1. Right -> Down -> Down
2. Down -> Down -> Right
3. Down -> Right -> Down
```

### Example 3

```text
Input: m = 7, n = 3
Output: 28
```

### Example 4

```text
Input: m = 3, n = 3
Output: 6
```
 
### Constraints

* `1 <= m, n <= 100`.
* It's guaranteed that the answer will be less than or equal to `2*10^9`.

## Solution 1: Recursive

At each point, the robot has two ways of moving: right or down. Let `P(m,n)` is the wanted result. Then you have a recursive relationship:

```text
P(m,n) = P(m-1, n) + P(m, n-1)
```

If the grid has only one row or only one column, then there is only one possible path.

```text
P(1, n) = P(m, 1) = 1.
```

Here's a recursive implementation.

### Code

```cpp
#include <iostream>
#include <vector>
using namespace std;
int uniquePaths(int m, int n) {
    if (m == 1 || n == 1) {
        return 1;
    }
    return uniquePaths(m - 1, n) + uniquePaths(m, n - 1);
}
int main() {
    std::cout << uniquePaths(3,7) << std::endl;
    std::cout << uniquePaths(7,3) << std::endl;
    std::cout << uniquePaths(3,2) << std::endl;
    std::cout << uniquePaths(3,3) << std::endl;
}
```

```text
Output:
28
28
3
6
```

This is a recursive solution that breaks down the problem into two subproblems:

- `uniquePaths(m-1, n)` 
- `uniquePaths(m, n-1)`

Each recursive call reduces either the `m` or `n` value by 1. 

The base case is when `m == 1` or `n == 1`, where there is only 1 unique path.

### Complexity

To calculate the complexity, let's look at the recursion tree:

- `uniquePaths(m,n)` calls:
  - `uniquePaths(m-1,n)`
  - `uniquePaths(m, n-1)`
- Each of those calls two more calls and so on.

The height of the tree will be `max(m,n)`. At each level, there are 2 branches.

So the total number of nodes in the tree will be `2^max(m,n)`.

Since each node represents a function call, the runtime complexity is `O(2^max(m,n))`.

The space complexity is `O(max(m,n))` due to the call stack.

In summary, the complexities are:

* Runtime: `O(2^max(m,n)`, where `m x n` is the size of the grid.
* Extra space: `O(max(m,n)`.

## Solution 2: Dynamic programming
The recursive implementation repeats a lot of computations.

For example, `uniquePaths(2,2)` was recomputed in both `uniquePaths(2,3)` and `uniquePaths(3,2)` when you compute `uniquePaths(3,3)`.

One way of storing what has been computed is by using dynamic programming.

### Code

```cpp
#include <iostream>
#include <vector>
using namespace std;
int uniquePaths(int m, int n) {
    // store what have been calculated in dp
    vector<vector<int> > dp(m, vector<int>(n,1));
    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
        }
    }
    return dp[m - 1][n - 1];
}
int main() {
    std::cout << uniquePaths(3,7) << std::endl;
    std::cout << uniquePaths(7,3) << std::endl;
    std::cout << uniquePaths(3,2) << std::endl;
    std::cout << uniquePaths(3,3) << std::endl;
}
```

```text
Output:
28
28
3
6
```

This solution uses dynamic programming to efficiently compute the number of unique paths in an `m x n` grid. It creates a 2D vector `dp` of size `m x n` and initializes all its values to 1 because there's exactly one way to reach any cell in the first row or first column.

Then, it iterates through the grid, starting from the second row and second column (i.e., indices (1, 1)), and for each cell, it calculates the number of unique paths to reach that cell. This is done by summing the number of paths from the cell above it and the cell to the left of it, as these are the only two possible directions to reach the current cell.

Finally, the value at `dp[m-1][n-1]` contains the total number of unique paths to reach the bottom-right corner of the grid, which is returned as the result.

### Complexity

* Runtime: `O(m*n)`, where `m x n` is the size of the grid.
* Extra space: `O(m*n)`.

## Solution 3: Reduced dynamic programming
You can rephrase the relationship inside the loop like this:

> "new value" = "old value" + "previous value";

Then you do not have to store all values of all rows.

### Code
```cpp
#include <iostream>
#include <vector>
using namespace std;
int uniquePaths(int m, int n) {
    // store the number of unique paths for each column in each row
    vector<int> dp(n, 1);
    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            dp[j] += dp[j - 1];
        }
    }
    return dp[n - 1];
}
int main() {
    std::cout << uniquePaths(3,7) << std::endl;
    std::cout << uniquePaths(7,3) << std::endl;
    std::cout << uniquePaths(3,2) << std::endl;
    std::cout << uniquePaths(3,3) << std::endl;
}
```

```text
Output:
28
28
3
6
```

### Complexity

* Runtime `O(m*n)`, where `m x n` is the size of the grid.
* Memory `O(n)`.

## Conclusion

Solution 3 uses only a 1D vector `dp` of size `n` to store the number of unique paths for each column.

First, it initializes all elements of `dp` to 1, as there's exactly one way to reach any cell in the first row or first column.

Then, it iterates through the grid, starting from the second row and second column (i.e., indices (1, 1)). For each cell, it updates the value in `dp` by adding the value from the cell directly above it and the value from the cell to the left of it. This step efficiently accumulates the number of unique paths to reach the current cell.

Finally, the value at `dp[n-1]` contains the total number of unique paths to reach the bottom-right corner of the grid, which is returned as the result.

### A bit of wonder

I am wondering if there is some mathematics behind this problem. Please share your finding if you find a formula for the solution to this problem.

## Exercise
- [Minimum Path Sum](https://leetcode.com/problems/minimum-path-sum/).

