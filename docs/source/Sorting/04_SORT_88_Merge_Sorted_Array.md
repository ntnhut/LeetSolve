# Merge Sorted Array

## [Problem statement](https://leetcode.com/problems/merge-sorted-array/)

You are given two integer arrays `nums1` and `nums2`, sorted in non-decreasing order, and two integers `m` and `n`, representing the number of elements in `nums1` and `nums2` respectively.

Merge `nums1` and `nums2` into a single array sorted in non-decreasing order.

The final sorted array should not be returned by the function, but instead be stored inside the array `nums1`. To accommodate this, `nums1` has a length of `m + n`, where the first `m` elements denote the elements that should be merged, and the last `n` elements are set to `0` and should be ignored. `nums2` has a length of `n`.

 

### Example 1
```text
Input: nums1 = [1,2,3,0,0,0], m = 3, nums2 = [2,5,6], n = 3
Output: [1,2,2,3,5,6]
Explanation: The arrays we are merging are [1,2,3] and [2,5,6].
The result of the merge is [1,2,2,3,5,6] with the underlined elements coming from nums1.
```

### Example 2
```text
Input: nums1 = [1], m = 1, nums2 = [], n = 0
Output: [1]
Explanation: The arrays we are merging are [1] and [].
The result of the merge is [1].
```

### Example 3
```text
Input: nums1 = [0], m = 0, nums2 = [1], n = 1
Output: [1]
Explanation: The arrays we are merging are [] and [1].
The result of the merge is [1].
Note that because m = 0, there are no elements in nums1. The 0 is only there to ensure the merge result can fit in nums1.
```

### Constraints

* `nums1.length == m + n`.
* `nums2.length == n`.
* `0 <= m, n <= 200`.
* `1 <= m + n <= 200`.
* `-10^9 <= nums1[i], nums2[j] <= 10^9`.
 

**Follow up**: Can you come up with an algorithm that runs in `O(m + n)` time?

## Solution 1: Store the result in a new container

### Code
```cpp
#include <iostream>
#include <vector>
using namespace std;
void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    vector<int> result;
    int i = 0;
    int j = 0;
    while (i < m || j < n) {
        if (j == n) {
            result.push_back(nums1[i++]);
        } else if (i == m) {
            result.push_back(nums2[j++]);
        } else {
            result.push_back(nums1[i] < nums2[j] ? nums1[i++] : nums2[j++]);
        }
    }
    nums1.swap(result);
}
void printResult(vector<int>& nums1) {
    cout << "[";
    for (int n : nums1) {
        cout << n << ",";
    }
    cout << "]\n";
}
int main() {
    vector<int> nums1 = {1,2,3,0,0,0};
    vector<int> nums2 = {2,5,6};
    merge(nums1, 3, nums2, 3);
    printResult(nums1);
    nums1 = {1};
    nums2 = {};
    merge(nums1, 1, nums2, 0);
    printResult(nums1);
    nums1 = {0};
    nums2 = {1};
    merge(nums1, 0, nums2, 1);
    printResult(nums1);
}
```
```text
Output:
[1,2,2,3,5,6,]
[1,]
[1,]
```

### Complexity
* Runtime: `O(m + n)`, where `m + n = nums1.length, n = nums2.length`.
* Extra space: `O(m + n)`.

## Solution 2: Reassigning `nums1` backward


### Code
```cpp
#include <iostream>
#include <vector>
using namespace std;
void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {    
    int k = m + n - 1;
    int i = m - 1;
    int j = n - 1;
    while (k >= 0) {
        if (j < 0) {
            nums1[k--] = nums1[i--];
        } else if (i < 0) {
            nums1[k--] = nums2[j--];
        } else {
            nums1[k--] = nums1[i] > nums2[j] ? nums1[i--] : nums2[j--]; 
        }
    }
}
void printResult(vector<int>& nums1) {
    cout << "[";
    for (int n : nums1) {
        cout << n << ",";
    }
    cout << "]\n";
}
int main() {
    vector<int> nums1 = {1,2,3,0,0,0};
    vector<int> nums2 = {2,5,6};
    merge(nums1, 3, nums2, 3);
    printResult(nums1);
    nums1 = {1};
    nums2 = {};
    merge(nums1, 1, nums2, 0);
    printResult(nums1);
    nums1 = {0};
    nums2 = {1};
    merge(nums1, 0, nums2, 1);
    printResult(nums1);
}
```
```text
Output:
[1,2,2,3,5,6,]
[1,]
[1,]
```

### Complexity
* Runtime: `O(m + n)`, where `m + n = nums1.length, n = nums2.length`.
* Extra space: `O(1)`.



