# Wiggle Subsequence

## [Problem statement](https://leetcode.com/problems/wiggle-subsequence/)
A **wiggle sequence** is a sequence where the differences between successive numbers strictly alternate between positive and negative. The first difference (if one exists) may be either positive or negative. A sequence with one element and a sequence with two non-equal elements are trivially wiggle sequences.

* For example, `[1, 7, 4, 9, 2, 5]` is a wiggle sequence because the differences `(6, -3, 5, -7, 3)` alternate between positive and negative.
* In contrast, `[1, 4, 7, 2, 5]` and `[1, 7, 4, 5, 5]` are not wiggle sequences. The first is not because its first two differences are positive, and the second is not because its last difference is zero.

A **subsequence** is obtained by deleting some elements (possibly zero) from the original sequence, leaving the remaining elements in their original order.

Given an integer array `nums`, return the length of the longest wiggle subsequence of `nums`.

 

### Example 1
```text
Input: nums = [1,7,4,9,2,5]
Output: 6
Explanation: The entire sequence is a wiggle sequence with differences (6, -3, 5, -7, 3).
```

### Example 2
```text
Input: nums = [1,17,5,10,13,15,10,5,16,8]
Output: 7
Explanation: There are several subsequences that achieve this length.
One is [1, 17, 10, 13, 10, 16, 8] with differences (16, -7, 3, -3, 6, -8).
```

### Example 3
```text
Input: nums = [1,2,3,4,5,6,7,8,9]
Output: 2
``` 

### Constraints

* `1 <= nums.length <= 1000`.
* `0 <= nums[i] <= 1000`.
 

**Follow up**: Could you solve this in $O(n)$ time?

## Solution: Counting the local extrema of `nums`

First, if you pick all local extrema (minima and maxima) of `nums` to form a subsequence `e`, then it is wiggle. Let us call it an **extrema** subsequence.

### Example 2
For `nums = [1,17,5,10,13,15,10,5,16,8]`, the local extrema are `[1,17,5,15,5,16,8]`. It is wiggle and called **extrema** subsequence.

Note that if `nums.length = n` then `nums[0]` and `nums[n - 1]` are always the first and the last extremum.

Second, given any two successive local extrema `a` and `b`, you cannot have any wiggle subsequence between them. Because the elements between them are either monotonic increasing or decreasing. 

That proves the extrema subsequence is the longest wiggle one.

### Code
```cpp
#include <iostream>
#include <vector>
using namespace std;
int wiggleMaxLength(vector<int>& nums) {
    // nums[0] is always the first extremum
    // start to find the second extremum
    int i = 1;
    while (i < nums.size() && nums[i] == nums[i - 1]) {
        i++;
    }
    if (i == nums.size()) {
        // all nums[i] are equal
        return 1;
    }
    int sign = nums[i] > nums[i - 1] ? 1 : -1;
    int count = 2;
    i++;
    while (i < nums.size()) {
        if ((nums[i] - nums[i - 1]) * sign < 0) {
            // nums[i] is an extremum
            count++;
            sign = -sign;
        }
        i++;
    }
    return count;
}
int main() {
    vector<int> nums{1,7,4,9,2,5};
    cout << wiggleMaxLength(nums) << endl;
    nums = {1,17,5,10,13,15,10,5,16,8};
    cout << wiggleMaxLength(nums) << endl;
    nums = {1,2,3,4,5,6,7,8,9};
    cout << wiggleMaxLength(nums) << endl;
}
```
```text
Output:
6
7
2
```

### Code explanation

1. The code initializes `i` to 1 and iterates while `i` is within the bounds of the `nums` array and while `nums[i]` is equal to `nums[i - 1]`. This loop is used to skip consecutive equal elements at the beginning of the array, ensuring that we start with a sequence where the first two elements are not equal.

2. After exiting the above loop, it checks if `i` has reached the end of the array (`i == nums.size()`). If it has, that means all elements in the array are equal, and we consider this as a valid wiggle subsequence of length 1. So, we return 1.

3. The code then initializes the `sign` variable based on whether `nums[i]` is greater than `nums[i - 1]`. If `nums[i] > nums[i - 1]`, set `sign` to 1; otherwise, set it to -1. This is done to determine whether we are currently increasing or decreasing in the wiggle subsequence.

4. It starts iterating from `i` again and check if `(nums[i] - nums[i - 1]) * sign < 0`. This condition checks if the difference between the current element and the previous element has changed the direction of the wiggle subsequence. If it has, we increment the `count` and reverse the `sign` (from 1 to -1 or from -1 to 1) to indicate the change in direction.

5. The code continues iterating through the rest of the array, repeating step 4 for each element.

6. Finally, it returns the `count`, which represents the maximum length of the wiggle subsequence.

In essence, the code identifies consecutive equal elements at the beginning, sets the initial direction, and then counts the number of times the direction changes to determine the length of the wiggle subsequence.

### Complexity
* Runtime: `O(n)`, where `n = nums.length`.
* Extra space: `O(1)`.



