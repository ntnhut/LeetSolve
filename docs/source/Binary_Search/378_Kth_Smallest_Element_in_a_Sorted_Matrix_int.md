# Kth Smallest Element in a Sorted Matrix

## [Problem statement](https://leetcode.com/problems/kth-smallest-element-in-a-sorted-matrix/)

You are given an `n x n` matrix where each row and column is sorted in ascending order. Your task is to find the `k-th` smallest element in this matrix.

Please note that we are looking for the `k-th` smallest element based on its position in the sorted order, and not counting distinct elements.

Additionally, it is required to find a solution with a memory complexity better than `O(n^2)`. 

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
int kthSmallest(vector<vector<int>>& matrix, int k) 
{
    vector<int> m;
    for (auto& row : matrix) 
    {
        m.insert(m.end(), row.begin(), row.end());
    }
    sort(m.begin(), m.end());
    return m.at(k - 1);
}
int main() 
{
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

### Code explanation

1. To simplify the problem, the code starts by flattening the 2D matrix into a 1D vector named `m`. It does this by iterating through each row of the matrix and appending the elements of each row to the end of the `m` vector.

2. After flattening the matrix, the code uses the `sort` function from the C++ Standard Library to sort the `m` vector in ascending order. This step ensures that all elements in the vector are in sorted order.

3. Finally, the code returns the `k`-th smallest element from the sorted `m` vector. Since the vector is 0-based indexed, the `k`-th smallest element corresponds to the element at index `k - 1` in the sorted vector.


### Complexity
The core idea behind this solution is to transform the 2D matrix into a 1D sorted array, making it easier to find the `k`-th smallest element efficiently. The time complexity of this solution is dominated by the sorting step, which is `O(N*logN)`, where `N` is the total number of elements in the matrix.

* Runtime: `O(N*logN)`, where `N = n^2` is the total number of elements in the matrix.
* Extra space: `O(N)`.

## Solution 2: Build the max heap and keep it ungrown

Instead of sorting after building the vector in Solution 1, you can do the other way around. It means building up the vector from scratch and keeping it sorted. 

Since you need only the `k-th` smallest element, [`std::priority_queue`](https://en.cppreference.com/w/cpp/container/priority_queue) can be used for this purpose.

### Code
```cpp
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
int kthSmallest(vector<vector<int>>& matrix, int k) 
{
    priority_queue<int> q;
    for (int row = 0; row < matrix.size(); row++) 
    {
        for (int col = 0; col < matrix[row].size(); col++) 
        {
            q.push(matrix[row][col]);
            if (q.size() > k) 
            {
                q.pop();
            }
        }
    }
    return q.top();
}
int main() 
{
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

### Code explanation

1. The code initializes a `priority_queue` named `q`, which is a min-heap. This min-heap will be used to keep track of the smallest `k` elements encountered in the matrix.

2. The code uses two nested loops to iterate through the matrix elements. The outer loop iterates over each row, and the inner loop iterates over each column within the row.

3. For each element in the matrix (represented by `matrix[row][col]`), the code pushes it into the priority queue `q`. This operation effectively adds the element to the heap while maintaining the heap property (smallest element at the top).

4. After pushing an element into the priority queue, the code checks if the size of the priority queue `q` exceeds the value of `k`. If it does, it means there are more than `k` elements in the priority queue. To ensure that the priority queue contains only the smallest `k` elements, the code uses the `pop` operation to remove the top (smallest) element from the priority queue. This step keeps the size of the priority queue constant at `k`.

5. After processing all elements in the matrix, the priority queue `q` will contain the smallest `k` elements, with the `k`-th smallest element at the top of the priority queue. The code returns the top element of the priority queue using `q.top()`, which is the `k`-th smallest element in the matrix.


### Complexity
The key idea behind this solution is to maintain a priority queue of size `k`, allowing it to efficiently keep track of the `k`-th smallest element encountered while iterating through the matrix. This approach is handy for large matrices, as it doesn't require sorting the entire matrix. 

* Runtime: `O(N*logk)`, where `N = n^2` is the total number of elements of the matrix.
* Extra space: `O(k)`.

## Solution 3: Binary search

Since the matrix is somehow sorted, you can perform the binary search algorithm. 

But the criteria for the search is not the value of the element `x` of interest; it is the number of elements that are less than or equal to `x` must be exactly `k`. You can use [`std::upper_bound`](https://en.cppreference.com/w/cpp/algorithm/upper_bound) for this purpose.

### Code
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int countLessOrEqual(const vector<vector<int>>& matrix, int x) 
{
    int count = 0;
    for (const auto& row : matrix) 
    {
        count += upper_bound(row.begin(), row.end(), x) - row.begin();
    }
    return count;
}
int kthSmallest(vector<vector<int>>& matrix, int k) 
{   
    int left = matrix.front().front();
    int right = matrix.back().back();
    while (left <= right) 
    {
        int mid = left + (right - left) / 2;
        if (countLessOrEqual(matrix, mid) >= k) 
        {
            right = mid - 1;
        } 
        else 
        {
            left = mid + 1; 
        }
    }
    return left;
}
int main() 
{
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

### Code explanation

1. The function **`countLessOrEqual`** counts the number of elements in the matrix that are less than or equal to a given value `x`.
   - It iterates through each row of the matrix.
   - For each row, it uses the `upper_bound` function from the C++ Standard Library to find the position of the first element greater than `x`. By subtracting the iterator obtained from `upper_bound` by the beginning of the row, it calculates the count of elements less than or equal to `x` in that row and adds it to the `count`.
   - Finally, it returns the total count.

2. The function **`kthSmallest`** finds the `k`-th smallest element in the matrix using a binary search approach.
   - It initializes two variables, `left` and `right`, to represent the minimum and maximum possible values in the matrix. `left` is set to the smallest element in the first row, and `right` is set to the largest element in the last row.
   - It enters a binary search loop where it continuously narrows down the search range by calculating the `mid` value as the average of `left` and `right`.
   - In each iteration, it calls the `countLessOrEqual` function to count how many elements in the matrix are less than or equal to `mid`.
   - If the count is greater than or equal to `k`, it updates `right` to `mid - 1`, effectively narrowing the search range to the left half.
   - If the count is less than `k`, it updates `left` to `mid + 1`, narrowing the search range to the right half.
   - The binary search continues until `left` is greater than `right`, at which point it has found the kth smallest element.
   - It returns `left` as the `k`-th smallest element.

The binary search in the `kthSmallest` function efficiently narrows the search range based on the count of elements less than or equal to the mid-point value. This is a highly efficient approach for large matrices.

### Complexity

1. The binary search in the `kthSmallest` function iterates until `left` is greater than `right`. In each iteration, it calculates the `mid` value as the average of `left` and `right`. 

2. In each iteration of the binary search, the `countLessOrEqual` function is called. This function iterates through each row of the matrix and performs an `upper_bound` operation on that row. The `upper_bound` operation has a time complexity of `O(logn)` for each row, where `n` is the number of elements in a row. The worst-case time complexity of the `countLessOrEqual` function is `O(n*logn)` for a single call.

4. In the binary search, the search range is continuously halved with each iteration. Therefore, the number of binary search iterations required to converge to the final answer is `O(log(max-min))`, where `max` and `min` are the maximum and minimum possible values in the matrix.

5. Combining the above points, the overall time complexity of the `kthSmallest` function is `O(log(max-min)) * O(n*logn)`.

In summary:

* Runtime: `O(n*logn*log(max -min))`, where `n` is the number of rows/columns of the matrix, `max` and `min` are the maximum and minimum possible values in the matrix..
* Extra space: `O(1)`.
