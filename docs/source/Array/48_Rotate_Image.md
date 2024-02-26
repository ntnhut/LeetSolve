# Rotate Image
% Medium 

## Problem statement

[^url]Given an `n x n` 2D matrix representing an image, your task is to rotate the image by 90 degrees clockwise. The rotation must be performed in-place, meaning you need to modify the original input 2D matrix directly. It is not allowed to create another 2D matrix for the rotation.

[^url]: https://leetcode.com/problems/rotate-image/
### Example 1

\begin{equation*}
\begin{bmatrix}
1 & 2 & 3 \\
4 & 5 & 6 \\
7 & 8 & 9
\end{bmatrix}
\longrightarrow
\begin{bmatrix}
7 & 4 & 1 \\
8 & 5 & 2 \\
9 & 6 & 3
\end{bmatrix}
\end{equation*}

```text
Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
Output: [[7,4,1],[8,5,2],[9,6,3]]
```

### Example 2

\begin{equation*}
\begin{bmatrix}
5 & 1 & 9 & 11 \\
2 & 4 & 8 & 10 \\
13 & 3 & 6 & 7 \\
15 & 14 & 12 & 16
\end{bmatrix}
\longrightarrow
\begin{bmatrix}
15 & 13 & 2 & 5 \\
14 & 3 & 4 & 1 \\
12 & 6 & 8 & 9 \\
16 & 7 & 10 & 11
\end{bmatrix}
\end{equation*}

```text
Input: matrix = [[5,1,9,11],[2,4,8,10],[13,3,6,7],[15,14,12,16]]
Output: [[15,13,2,5],[14,3,4,1],[12,6,8,9],[16,7,10,11]]
``` 

### Constraints

* `n == matrix.length == matrix[i].length`.
* `1 <= n <= 20`.
* `-1000 <= matrix[i][j] <= 1000`.

## Solution: The math behind

For any square matrix, the rotation 90 degrees clockwise can be performed in two steps:

1. Transpose the matrix.
2. Mirror the matrix vertically.

### Code
```cpp
#include <iostream>
#include <vector>
using namespace std;
void rotate(vector<vector<int>>& matrix) {
    const int n = matrix.size();
    // transpose
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            swap(matrix[i][j], matrix[j][i]);
        }
    }
    // vertical mirror
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n / 2; j++ ) {
            swap(matrix[i][j], matrix[i][n - 1 - j]);
        }
    }
}
void printMatrix(const vector<vector<int>>& matrix) {
    cout << "[";
    for (auto& row: matrix) {
        cout << "[";
        for (auto& a: row) {
            cout << a << ",";
        }
        cout << "],";
    }
    cout << "]\n";
}
int main() {
    vector<vector<int>> matrix{{1,2,3},{4,5,6},{7,8,9}};
    rotate(matrix);
    printMatrix(matrix);
    matrix = {{5,1,9,11},{2,4,8,10},{13,3,6,7},{15,14,12,16}};
    rotate(matrix);
    printMatrix(matrix);
}
```
```text
Output:
[[7,4,1,],[8,5,2,],[9,6,3,],]
[[15,13,2,5,],[14,3,4,1,],[12,6,8,9,],[16,7,10,11,],]
```

### Complexity
* Runtime: `O(n^2)`, where `n = matrix.length`.
* Extra space: `O(1)`.

## Implementation tips

1. The function {index}`std::swap`[^swapurl] can be used to exchange two values.

2. When doing the transpose or mirroring, you could visit over only one-half of the matrix.

[^swapurl]: https://en.cppreference.com/w/cpp/algorithm/swap
## Exercise
- [Determine Whether Matrix Can Be Obtained By Rotation](https://leetcode.com/problems/determine-whether-matrix-can-be-obtained-by-rotation/) 