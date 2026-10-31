# 48. Rotate Image

## Problem Statement

Given an `n x n` 2D matrix representing an image, rotate the image by 90 degrees clockwise. The rotation must be performed in-place, meaning you need to modify the original input 2D matrix directly. It is not allowed to create another 2D matrix for the rotation.

### Example 1

```text
Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
Output: [[7,4,1],[8,5,2],[9,6,3]]
```

The transformation can also be visualized as:

```text
1 2 3       7 4 1
4 5 6   ->  8 5 2
7 8 9       9 6 3
```

### Example 2

```text
Input: matrix = [[5,1,9,11],[2,4,8,10],[13,3,6,7],[15,14,12,16]]
Output: [[15,13,2,5],[14,3,4,1],[12,6,8,9],[16,7,10,11]]
```

### Constraints

- `n == matrix.length == matrix[i].length`
- `1 <= n <= 20`
- `-1000 <= matrix[i][j] <= 1000`

---

## First Intuition

A direct way to rotate a matrix is to move every value to its new row and column. But building a second matrix would make the mapping straightforward at the cost of violating the in-place requirement.

Instead, look for simple transformations that can be performed by swapping values in place. Transposing a matrix reflects it across its main diagonal. Reversing each row then reflects the result horizontally. Together, those two operations produce a 90-degree clockwise rotation without allocating another matrix.

---

## Approach: Transpose, Then Reverse Each Row

### Idea

Consider where an element at row `i`, column `j` should go after a clockwise rotation: it moves to row `j`, column `n - 1 - i`.

The two transformations achieve that mapping in sequence:

1. **Transpose:** swap `matrix[i][j]` with `matrix[j][i]`. Visit only the cells above the main diagonal, so each pair is swapped once.
2. **Reverse each row:** swap the leftmost and rightmost entries, moving inward.

For a `3 x 3` matrix, the transpose changes each element's row and column. Reversing each resulting row then places the columns in the order required for a clockwise rotation.

### Code

```cpp
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

void rotate(vector<vector<int>>& matrix) {
    const int n = matrix.size();

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            swap(matrix[i][j], matrix[j][i]);
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n / 2; j++) {
            swap(matrix[i][j], matrix[i][n - 1 - j]);
        }
    }
}

void printMatrix(const vector<vector<int>>& matrix) {
    cout << "[";
    for (const auto& row : matrix) {
        cout << "[";
        for (int value : row) {
            cout << value << ",";
        }
        cout << "],";
    }
    cout << "]\n";
}

int main() {
    vector<vector<int>> matrix{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    rotate(matrix);
    printMatrix(matrix);

    matrix = {{5, 1, 9, 11}, {2, 4, 8, 10},
              {13, 3, 6, 7}, {15, 14, 12, 16}};
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

- **Time:** `O(n^2)`, because both transformations visit a constant fraction of the `n * n` cells.
- **Space:** `O(1)` extra space, since the swaps happen inside the original matrix.

### Common Pitfalls

- During transpose, start the inner loop at `j = i + 1`. Swapping both sides of the diagonal would undo the first swaps.
- During row reversal, visit only half of each row. Swapping every position would reverse the row and then reverse it back.
- This method relies on the matrix being square, as guaranteed by the problem.

---

## Key Takeaways

- Break a geometric transformation into simpler in-place operations.
- A transpose swaps rows and columns; reversing each row after the transpose gives a clockwise rotation.
- When swapping symmetric pairs, process only one side to avoid undoing the transformation.

---

## References and Further Reading

- [LeetCode 48. Rotate Image](https://leetcode.com/problems/rotate-image/)
- [`std::swap`](https://en.cppreference.com/w/cpp/algorithm/swap)

### Related LeetCode Problems

- [1886. Determine Whether Matrix Can Be Obtained By Rotation](https://leetcode.com/problems/determine-whether-matrix-can-be-obtained-by-rotation/): Applies repeated matrix rotations to compare two matrices.

### Patterns Used

- In-place matrix transformation
- Transpose and reflection
