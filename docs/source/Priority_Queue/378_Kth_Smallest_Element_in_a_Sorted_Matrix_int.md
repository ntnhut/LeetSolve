# Kth Smallest Element in a Sorted Matrix
% Medium 
## Problem statement

[^url]You are given an `n x n` matrix where each row and column is sorted in ascending order. Your task is to find the `k-th` smallest element in this matrix.

Please note that we are looking for the `k-th` smallest element based on its position in the sorted order, and not counting distinct elements.

Additionally, it is required to find a solution with a memory complexity better than `O(n^2)`. 

[^url]: https://leetcode.com/problems/kth-smallest-element-in-a-sorted-matrix/
### Example 1
```text
Input: matrix = [[1,5,9],[10,11,13],[12,13,15]], k = 8
Output: 13
Explanation: The elements in the matrix are [1,5,9,10,11,12,13,13,15], and the 8th smallest number is 13
```

### Example 2
```text
Input: matrix = [[-5]], k = 1
Output: -5
``` 

### Constraints

* `n == matrix.length == matrix[i].length`.
* `1 <= n <= 300`.
* `-10^9 <= matrix[i][j] <= 10^9`.
* All the rows and columns of `matrix` are guaranteed to be sorted in non-decreasing order.
* `1 <= k <= n^2`.
 

### Follow up

* Could you solve the problem with a constant memory (i.e., `O(1)` memory complexity)?
* Could you solve the problem in `O(n)` time complexity? The solution may be too advanced for an interview but you may find reading [this paper](http://www.cse.yorku.ca/~andy/pubs/X+Y.pdf) fun.

## Solution 1: Transform the 2-D matrix into a 1-D vector then sort

You can implement exactly what Example 1 has explained.

### Code

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int kthSmallest(vector<vector<int>>& matrix, int k) {
    vector<int> m;
    for (auto& row : matrix) {
        m.insert(m.end(), row.begin(), row.end());
    }
    sort(m.begin(), m.end());
    return m.at(k - 1);
}
int main() {
    vector<vector<int>> matrix{{1,5,9},{10,11,13},{12,13,15}};
    cout << kthSmallest(matrix, 8) << endl;
    matrix = {{-5}};
    cout << kthSmallest(matrix, 1) << endl;
}
```
```text
Output:
13
-5
```

The core idea behind this solution is to transform the 2D matrix into a 1D sorted array, making it easier to find the `k`-th smallest element efficiently. The time complexity of this solution is dominated by the sorting step, which is `O(N*logN)`, where `N` is the total number of elements in the matrix.

### Complexity

* Runtime: `O(N*logN)`, where `N = n^2` is the total number of elements in the matrix.
* Extra space: `O(N)`.

## Solution 2: Build the max heap and keep it ungrown

Instead of sorting after building the vector in Solution 1, you can do the other way around. It means building up the vector from scratch and keeping it sorted. 

Since you need only the `k-th` smallest element, {index}`std::priority_queue`[](https://en.cppreference.com/w/cpp/container/priority_queue) can be used for this purpose.

### Code
```cpp
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
int kthSmallest(vector<vector<int>>& matrix, int k) {
    priority_queue<int> q;
    for (int row = 0; row < matrix.size(); row++) {
        for (int col = 0; col < matrix[row].size(); col++) {
            q.push(matrix[row][col]);
            if (q.size() > k) {
                q.pop();
            }
        }
    }
    return q.top();
}
int main() {
    vector<vector<int>> matrix{{1,5,9},{10,11,13},{12,13,15}};
    cout << kthSmallest(matrix, 8) << endl;
    matrix = {{-5}};
    cout << kthSmallest(matrix, 1) << endl;
}
```
```text
Output:
13
-5
```

This solution maintains a priority queue of size `k`, allowing it to efficiently keep track of the `k`-th smallest element encountered while iterating through the matrix. 

This approach is handy for large matrices, as it doesn't require sorting the entire matrix. 

### Complexity

* Runtime: `O(N*logk)`, where `N = n^2` is the total number of elements of the matrix.
* Extra space: `O(k)`.

## Solution 3: Binary search

Since the matrix is somehow sorted, you can perform the binary search algorithm. 

But the criteria for the searching is not the value of the element `x` of interest; it is the number of elements that less than or equal to `x` must be exactly `k`. You can use {index}`std::upper_bound`[](https://en.cppreference.com/w/cpp/algorithm/upper_bound) for this purpose.

### Code
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int countLessOrEqual(const vector<vector<int>>& matrix, int x) {
    int count = 0;
    for (const auto& row : matrix) {
        count += upper_bound(row.begin(), row.end(), x) - row.begin();
    }
    return count;
}
int kthSmallest(vector<vector<int>>& matrix, int k) {   
    int left = matrix.front().front();
    int right = matrix.back().back();
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (countLessOrEqual(matrix, mid) >= k) {
            right = mid - 1;
        } else {
            left = mid + 1; 
        }
    }
    return left;
}
int main() {
    vector<vector<int>> matrix{{1,5,9},{10,11,13},{12,13,15}};
    cout << kthSmallest(matrix, 8) << endl;
    matrix = {{-5}};
    cout << kthSmallest(matrix, 1) << endl;
}
```
```text
Output:
13
-5
```

This solution utilizes binary search along with a counting mechanism to efficiently find the kth smallest element in a sorted matrix. The `countLessOrEqual` function counts the number of elements less than or equal to a given value `x` in the matrix, leveraging the fact that each row in the matrix is sorted. 

The `kthSmallest` function then utilizes binary search to find the smallest value `mid` such that the number of elements less than or equal to `mid` is greater than or equal to `k`. 

This approach effectively narrows down the search space by iteratively adjusting the search range based on the count of elements, ultimately identifying the kth smallest element efficiently.

### Complexity

1. In each iteration of the binary search, the `countLessOrEqual` function is called. This function iterates through each row of the matrix and performs an `upper_bound` operation on that row. The `upper_bound` operation has a time complexity of `O(logn)` for each row, where `n` is the number of elements in a row. The worst-case time complexity of the `countLessOrEqual` function is `O(n*logn)` for a single call.

2. In the binary search, the search range is continuously halved with each iteration. Therefore, the number of binary search iterations required to converge to the final answer is `O(log(max-min))`, where `max` and `min` are the maximum and minimum possible values in the matrix.

3. Combining the above points, the overall time complexity of the `kthSmallest` function is `O(log(max-min)) * O(n*logn)`.

In summary:

* Runtime: `O(n*logn*log(max -min))`, where `n` is the number of rows/columns of the matrix, `max` and `min` are the maximum and minimum possible values in the matrix.
* Extra space: `O(1)`.

## Exercise
- [Find K Pairs with Smallest Sums](https://leetcode.com/problems/find-k-pairs-with-smallest-sums/)