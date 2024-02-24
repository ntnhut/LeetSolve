# Transpose Matrix
% Easy 

## Problem statement

[^url]You are given a 2D integer array `matrix`, and your objective is to find the transpose of the given matrix.

The transpose of a matrix involves flipping the matrix over its main diagonal, effectively swapping its row and column indices.
 
\begin{equation*}
\begin{bmatrix}
1 & 2 & 3 \\
4 & 5 & 6 \\
7 & 8 & 9
\end{bmatrix}
\longrightarrow
\begin{bmatrix}
1 & 4 & 7 \\
2 & 5 & 8 \\
3 & 6 & 9
\end{bmatrix}
\end{equation*}

[^url]: https://leetcode.com/problems/transpose-matrix/ 
### Example 1
```text
Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
Output: [[1,4,7],[2,5,8],[3,6,9]]
```

### Example 2
```text
Input: matrix = [[1,2,3],[4,5,6]]
Output: [[1,4],[2,5],[3,6]]
``` 

### Constraints

* `m == matrix.length`.
* `n == matrix[i].length`.
* `1 <= m, n <= 1000`.
* `1 <= m * n <= 10^5`.
* `-10^9 <= matrix[i][j] <= 10^9`.

## Solution

### Code
```cpp
#include <iostream>
#include <vector>
using namespace std;
vector<vector<int>> transpose(vector<vector<int>>& matrix) {
    // declare the transposed matrix mt of desired size, i.e.
    // mt's number of rows = matrix's number of columns (matrix[0].size())
    // mt's number of columns = matrix's number of rows (matrix.size())
    vector<vector<int>> mt(matrix[0].size(), 
                           vector<int>(matrix.size()));
    for (int i = 0; i < mt.size(); i++) {
        for (int j = 0; j < mt[i].size(); j++) {
            mt[i][j] = matrix[j][i];
        }
    }
    return mt;
}
void printResult(vector<vector<int>>& matrix) {
    cout << "[";
    for (auto row : matrix) {
        cout << "[";
        for (int m : row) {
            cout << m << ",";
        }
        cout << "]";
    }
    cout << "]\n";
}
int main() {
    vector<vector<int>> matrix = {{1,2,3},{4,5,6},{7,8,9}};
    auto result = transpose(matrix);
    printResult(result);
    matrix = {{1,2,3},{4,5,6}};
    result = transpose(matrix);
    printResult(result);
}
```
```text
Output:
[[1,4,7,][2,5,8,][3,6,9,]]
[[1,4,][2,5,][3,6,]]
```

### Complexity
* Runtime: `O(m*n)`, where `m = matrix.length` and `n = matrix[i].length`.
* Extra space: `O(1)`.


## Implementation note

Note that the matrix might not be square, you cannot just swap the elements using for example the function [`std::swap`](https://en.cppreference.com/w/cpp/algorithm/swap).

