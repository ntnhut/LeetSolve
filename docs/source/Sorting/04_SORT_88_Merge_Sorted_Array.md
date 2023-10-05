# Merge Sorted Array

## [Problem statement](https://leetcode.com/problems/merge-sorted-array/)

You're given two integer arrays, `nums1` and `nums2`, both sorted in non-decreasing order. Additionally, you have two integers, `m` and `n`, representing the number of elements in `nums1` and `nums2`, respectively.

Your task is to merge the elements from `nums2` into `nums1` in a way that the resulting array is sorted in non-decreasing order.

However, the sorted array should not be returned as a separate result. Instead, the merged elements should be stored inside the `nums1` array. Here's the setup for that purpose: 

* `nums1` has a total length of `m + n`, where the first `m` elements represent the elements that should be merged, and the last `n` elements are initialized to `0` and should be ignored. 
* The `nums2` array has a length of `n`, representing the elements to be merged from `nums2` into the final `nums1` array. 

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

### Code explanation

1. The code begins by initializing an empty vector called `result`, which will be used to store the merged values.

2. Next, it sets up two pointers, `i` and `j`, initially both at position `0`, to track our progress within the `nums1` and `nums2` arrays, respectively.

3. Inside the loop, it handles three possible scenarios:
   - If `j` reaches `n`, indicating that it has exhausted all elements in `nums2`, it adds the current element from `nums1` (located at index `i`) to the `result` vector, and then increments `i`.

   - If `i` reaches `m`, indicating that it has exhausted all elements in `nums1`, it adds the current element from `nums2` (located at index `j`) to the `result` vector, and then increments `j`.

   - If neither of the above conditions is met, it compares the current elements at `nums1[i]` and `nums2[j]`. It selects the smaller element, adds it to the `result` vector, and increments the corresponding pointer (`i` or `j`) accordingly.

4. Once the while loop completes, it has successfully merged all elements from both arrays into the `result` vector.

5. Finally, it replaces the contents of `nums1` with the contents of the `result` vector using the `swap` method, effectively updating `nums1` with the merged and sorted values.


### Complexity
This solution merges two sorted arrays `nums1` and `nums2` into `nums1` while maintaining sorted order. It iterates through both arrays, comparing elements and adding them to a temporary `result` vector. After the merging is complete, it replaces the contents of `nums1` with the merged result. 

* Runtime: `O(m+n)`, where `m = nums1.length` and `n = nums2.length`.
* Extra space: `O(m+n)`.

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

### Code explanation

1. The code initializes three pointers: `k`, `i`, and `j`. 
   - `k` is initialized to `m + n - 1`, which is the last index of the merged array.
   - `i` is initialized to `m - 1`, which is the last index of the `nums1` array.
   - `j` is initialized to `n - 1`, which is the last index of the `nums2` array.

2. Inside the loop, there are three possible scenarios to consider:

   - If `j` is less than 0, it means it has already processed all elements from `nums2`. In this case, it copies the remaining elements from `nums1` to `nums1[k]`, decrements both `k` and `i`, and moves to the next element in `nums1`.

   - If `i` is less than 0, it means it has already processed all elements from `nums1`. In this case, it copies the remaining elements from `nums2` to `nums1[k]`, decrements both `k` and `j`, and moves to the next element in `nums2`.

   - If neither of the above conditions is met, it compares the current elements at `nums1[i]` and `nums2[j]`. It selects the larger element and places it in `nums1[k]`, effectively moving from the end of both arrays towards the beginning while preserving the sorted order. After the assignment, it decrements both `k` and the pointer (`i` or `j`) corresponding to the selected element.

3. This process continues until all elements from `nums1` and `nums2` have been merged into `nums1` while maintaining the sorted order.

4. When the while loop completes, `nums1` contains the merged and sorted elements of both `nums1` and `nums2`.


### Complexity
In summary, this solution efficiently merges two sorted arrays, `nums1` and `nums2`, into `nums1` while preserving the sorted order. It uses three pointers (`k`, `i`, and `j`) to perform the merge in reverse order, which helps avoid the need for additional space. 

* Runtime: `O(m+n)`, where `m = nums1.length` and `n = nums2.length`.
* Extra space: `O(1)`.
