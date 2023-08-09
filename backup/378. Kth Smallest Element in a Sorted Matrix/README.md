## 378. Kth Smallest Element in a Sorted Matrix

### Problem statement
Given an `n x n` matrix where each of the rows and columns is sorted in ascending order, return the `k-th` smallest element in the matrix.

Note that it is the `k-th` smallest element in the sorted order, not the `k-th` distinct element.

You must find a solution with a memory complexity better than `O(n^2)`.

 

#### Example 1
```plain
Input: matrix = [[1,5,9],[10,11,13],[12,13,15]], k = 8
Output: 13
Explanation: The elements in the matrix are [1,5,9,10,11,12,13,13,15], and the 8th smallest number is 13
```

#### Example 2
```plain
Input: matrix = [[-5]], k = 1
Output: -5
``` 

#### Constraints

* `n == matrix.length == matrix[i].length`.
* `1 <= n <= 300`.
* `-10^9 <= matrix[i][j] <= 10^9`.
* All the rows and columns of `matrix` are guaranteed to be sorted in non-decreasing order.
* `1 <= k <= n^2`.
 

#### Follow up

* Could you solve the problem with a constant memory (i.e., `O(1)` memory complexity)?
* Could you solve the problem in `O(n)` time complexity? The solution may be too advanced for an interview but you may find reading [this paper](http://www.cse.yorku.ca/~andy/pubs/X+Y.pdf) fun.

### Solution 1: Transform the 2-D matrix into an 1-D vector then sort

You can implement exactly what Example 1 has explained.

#### Code

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
    return m[k - 1];
}
int main() {
    vector<vector<int>> matrix{{1,5,9},{10,11,13},{12,13,15}};
    cout << kthSmallest(matrix, 8) << endl;
    matrix = {{-5}};
    cout << kthSmallest(matrix, 1) << endl;
}
```
```plain
Output:
13
-5
```

#### Complexity
* Runtime: `O(n^2*logn)`, where `n x n` is the size of the matrix. Note that `log(n^2) = 2logn`.
* Extra space: `O(n^2)`.

### Solution 2: Build the max heap and keep it ungrown

Instead of sorting after building the vector in Solution 1, you can do the other way around. It means building up the vector from scratch and keeping it sorted. 

Since you need only the `k-th` smallest element, [`std::priority_queue`](https://en.cppreference.com/w/cpp/container/priority_queue) can be used for this purpose.

#### Code
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
```plain
Output:
13
-5
```

#### Complexity
* Runtime: `O(n^2*logk)`, where `n x n` is the size of the matrix.
* Extra space: `O(k)`.

### Solution 3: Binary search

Since the matrix is somehow sorted, you can perform the binary search algorithm on it. 

But the criteria for the searching is not the value of the element `x` of interest; it is the number of elements that less than or equal to `x` must be exactly `k`. You can use [`std::upper_bound`](https://en.cppreference.com/w/cpp/algorithm/upper_bound) for this purpose.

#### Code
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
```plain
Output:
13
-5
```

#### Complexity
* Runtime: `O(nlognlogM)`, where `n x n` is the size of the matrix, `M` is the difference between the maximum element and the minimum element of the matrix.
* Extra space: `O(1)`.

### References
* [https://leetcode.com/problems/kth-smallest-element-in-a-sorted-matrix/](https://leetcode.com/problems/kth-smallest-element-in-a-sorted-matrix/)
* [https://www.leetsolve.com/378-kth-smallest-element-in-a-sorted-matrix](https://www.leetsolve.com/378-kth-smallest-element-in-a-sorted-matrix)