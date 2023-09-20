# Transpose Matrix

## [Problem statement](https://leetcode.com/problems/transpose-matrix/)

You are given a 2D integer array `matrix`, and your objective is to find the transpose of the given matrix.

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
    vector<vector<int>> mt(matrix[0].size(), vector<int>(matrix.size()));
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

### Code explanation

1. The code initializes a new 2D vector `mt` to store the transpose of the input `matrix`. The number of rows in `mt` is equal to the number of columns in the original `matrix`, and the number of columns in `mt` is equal to the number of rows in the original `matrix`. This ensures that `mt` has the correct dimensions for the transpose.

2. The outer loop iterates through the rows of the `mt` matrix. Since the number of rows in `mt` is equal to the number of columns in the original `matrix`, this loop goes through the rows of the transposed matrix.

3. The inner loop iterates through the columns of the `mt` matrix. Since the number of columns in `mt` is equal to the number of rows in the original `matrix`, this loop goes through the columns of the transposed matrix.

4. Inside the nested loops, it assigns the value at the current row `j` and column `i` in the original `matrix` to the corresponding row `i` and column `j` in the transposed `mt` matrix. This effectively transposes the values from the original matrix to the transposed matrix.

5. After both loops have completed, the `mt` matrix contains the transpose of the original `matrix`.

6. Finally, the transposed matrix `mt` is returned as the result of the function.

In summary, this code computes the transpose of a given 2D matrix by creating a new matrix with swapped dimensions (rows become columns and vice versa) and copying values from the original matrix to the transposed matrix in the appropriate positions. The resulting transposed matrix is then returned.

### Complexity
* Runtime: `O(m*n)`, where `m = matrix.length` and `n = matrix[i].length`.
* Extra space: `O(1)`.


```{admonition} Implementation note
:class: note

Note that the matrix might not be square, you cannot just swap the elements using for example the function [`std::swap`](https://en.cppreference.com/w/cpp/algorithm/swap).

```
