# Spiral Matrix II

## [Problem statement](https://leetcode.com/problems/spiral-matrix-ii/)

Given a positive integer `n`, generate an `n x n` matrix filled with elements from `1` to `n^2` in spiral order.


### Example 1

![Example 1](59_spiraln.jpg)

```plain
Input: n = 3
Output: [[1,2,3],[8,9,4],[7,6,5]]
```
### Example 2
```plain
Input: n = 1
Output: [[1]]
``` 

### Constraints

* `1 <= n <= 20`.

## Solution 

1. Starting from the top left of the matrix.
2. Going along the spiral direction. 
3. Put the value to the matrix, starting from `1`.

### Code

```cpp
#include <vector>
#include <iostream>
using namespace std;
enum Direction {RIGHT, DOWN, LEFT, UP};
vector<vector<int>> generateMatrix(int n) 
{
    vector<vector<int>> m(n, vector<int>(n));
    int bottom = n - 1;
    int right = n - 1;
    int top = 0;
    int left = 0;
    int row = 0;
    int col = 0;
    Direction d = RIGHT;
    int a = 1;
    while (top <= bottom && left <= right) 
    {
        m[row][col] = a++;
        switch (d) 
        {
            case RIGHT:
                if (col == right) 
                {
                    top++;
                    d = DOWN;
                    row++;
                } 
                else 
                {
                    col++;
                }
                break;
            case DOWN:
                if (row == bottom) 
                {
                    right--;
                    d = LEFT;
                    col--;
                } 
                else 
                {
                    row++;
                }
                break;
            case LEFT:
                if (col == left) 
                {
                    bottom--;
                    d = UP;
                    row--;
                } 
                else 
                {
                    col--;
                }
                break;
            case UP:
                if (row == top) 
                {
                    left++;
                    d = RIGHT;
                    col++;
                } 
                else 
                {
                    row--;
                }
                break;
        }
    }
    return m;
}
void printResult(vector<vector<int>>& m) 
{
    cout << "[";
    for (auto& r : m) 
    {
        cout << "[";
        for (int a : r) 
        {
            cout << a << ",";
        }
        cout << "]";
    }
    cout << "]\n";
}
int main() 
{
    auto m = generateMatrix(3);
    printResult(m);
    m = generateMatrix(1);
    printResult(m);
}
```
```plain
Output:
[[1,2,3,][8,9,4,][7,6,5,]]
[[1,]]
```

### Code explanation 

1. The code creates a 2D vector `m` of size `n x n` to represent the square matrix. It initializes it with all zeros.

2. It defines variables `bottom`, `right`, `top`, and `left` to keep track of the boundaries of the matrix. Initially, they are set to the indexes of the outermost rows and columns of the matrix.

3. The code initializes `row` and `col` to 0, representing the current position in the matrix.

4. It creates an enumeration `Direction` to represent the current direction of movement (`RIGHT`, `DOWN`, `LEFT`, `UP`). It initializes `d` to `RIGHT` to start moving to the right.

5. The code initializes an integer `a` to 1, which will be used to fill the matrix with incrementing values.

6. It uses a while loop to traverse the matrix and fills it with values as long as the `top` boundary is less than or equal to the `bottom` boundary and the `left` boundary is less than or equal to the `right` boundary.

7. Inside the loop, it fills the current position `(row, col)` in the matrix with the value `a` and increment `a` by 1.

8. The code uses a {index}`switch` statement based on the current direction `d` to determine the next move:
   - If `d` is RIGHT, it checks if `col` has reached the `right` boundary. If it has, it moves to the next direction (`DOWN`) and update `row` accordingly; otherwise, increment `col`.
   - Similar logic is applied for the `DOWN`, `LEFT`, and `UP` directions, adjusting `row` and `col` accordingly and changing direction when needed.

9. Once the loop is complete, the matrix is filled in a spiral order, and the function returns the filled matrix.


### Complexity

* Runtime: `O(n^2)`, where `n x n` is the size of the matrix.
* Extra space: `O(1)`.

